#!/usr/bin/env bash

set -euo pipefail

IS_SOURCED=0
if [[ "${BASH_SOURCE[0]}" != "$0" ]]; then
  IS_SOURCED=1
fi

SOURCE_DIR="."
BUILD_DIR="build"
TARGET="app"
JOBS="4"
QT_BIN_PATH="${QT_BIN_PATH:-}"
MINGW_BIN_PATH="${MINGW_BIN_PATH:-}"
CONFIGURE_AND_BUILD=0

usage() {
  cat <<EOF
Usage: ./build-msys.sh [options]

Options:
  -s, --source-dir <dir>      Source directory (default: .)
  -b, --build-dir <dir>       Build directory (default: build)
  -t, --target <name>         Build target (default: app)
  -j, --jobs <n>              Parallel jobs for cmake --build (default: 4)
      --qt-bin <path>         Qt bin directory
      --mingw-bin <path>      MinGW bin directory
      --configure-and-build   Run cmake configure and build after setup
  -h, --help                  Show this help

Notes:
  1) Running './build-msys.sh' opens a shell in build dir with env configured.
  2) Use 'source ./build-msys.sh' if you prefer staying in current shell.
EOF
}

to_unix_path() {
  local input_path="$1"
  if [[ -z "$input_path" ]]; then
    return
  fi

  if command -v cygpath >/dev/null 2>&1; then
    cygpath -u "$input_path"
  else
    printf '%s\n' "$input_path"
  fi
}

add_to_path_if_exists() {
  local dir="$1"
  [[ -z "$dir" ]] && return

  local unix_dir
  unix_dir="$(to_unix_path "$dir")"

  if [[ -d "$unix_dir" ]]; then
    case ":$PATH:" in
      *":$unix_dir:"*) ;;
      *)
        PATH="$unix_dir:$PATH"
        export PATH
        echo "Added to PATH: $unix_dir"
        ;;
    esac
  else
    echo "Warning: directory not found, skipped PATH update: $dir" >&2
  fi
}

pick_first_existing_dir() {
  local candidate
  for candidate in "$@"; do
    if [[ -n "$candidate" && -d "$candidate" ]]; then
      printf '%s\n' "$candidate"
      return 0
    fi
  done
  return 1
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    -s|--source-dir)
      SOURCE_DIR="$2"
      shift 2
      ;;
    -b|--build-dir)
      BUILD_DIR="$2"
      shift 2
      ;;
    -t|--target)
      TARGET="$2"
      shift 2
      ;;
    -j|--jobs)
      JOBS="$2"
      shift 2
      ;;
    --qt-bin)
      QT_BIN_PATH="$2"
      shift 2
      ;;
    --mingw-bin)
      MINGW_BIN_PATH="$2"
      shift 2
      ;;
    --configure-and-build)
      CONFIGURE_AND_BUILD=1
      shift
      ;;
    -h|--help)
      usage
      return 0 2>/dev/null || exit 0
      ;;
    *)
      echo "Unknown argument: $1" >&2
      usage
      return 1 2>/dev/null || exit 1
      ;;
  esac
done

if [[ -z "$QT_BIN_PATH" ]]; then
  if [[ -n "${QTDIR:-}" ]]; then
    QT_BIN_PATH="$QTDIR/bin"
  elif [[ -n "${QT_DIR:-}" ]]; then
    QT_BIN_PATH="$QT_DIR/bin"
  else
    QT_BIN_PATH="$(pick_first_existing_dir \
      /c/Qt/Qt5.12.6/5.12.6/mingw73_32/bin \
      /c/Qt/5.12.10/mingw73_32/bin \
      /c/Qt/5.12.6/mingw73_32/bin \
      /c/Qt/6.*/mingw*/bin 2>/dev/null || true)"
  fi
fi

if [[ -z "$MINGW_BIN_PATH" ]]; then
  if [[ -n "${MINGW_HOME:-}" ]]; then
    MINGW_BIN_PATH="$MINGW_HOME/bin"
  else
    MINGW_BIN_PATH="$(pick_first_existing_dir \
      /c/Qt/Qt5.12.6/Tools/mingw730_32/bin \
      /c/Qt/Tools/mingw730_32/bin \
      /mingw64/bin \
      /usr/bin || true)"
  fi
fi

add_to_path_if_exists "$QT_BIN_PATH"
add_to_path_if_exists "$MINGW_BIN_PATH"

export CMAKE_GENERATOR="MSYS Makefiles"

echo "Session configured for MSYS build."
echo "CMAKE_GENERATOR=$CMAKE_GENERATOR"

MAKE_PROGRAM=""
if command -v make >/dev/null 2>&1; then
  MAKE_PROGRAM="$(command -v make)"
elif command -v mingw32-make >/dev/null 2>&1; then
  MAKE_PROGRAM="$(command -v mingw32-make)"
fi

CC_BIN=""
CXX_BIN=""
AR_BIN=""
if command -v gcc >/dev/null 2>&1; then
  CC_BIN="$(command -v gcc)"
fi
if command -v g++ >/dev/null 2>&1; then
  CXX_BIN="$(command -v g++)"
fi
if command -v ar >/dev/null 2>&1; then
  AR_BIN="$(command -v ar)"
fi

if [[ -z "$MAKE_PROGRAM" ]]; then
  echo "Error: make tool not found (neither make nor mingw32-make)." >&2
  echo "Set --mingw-bin to your MinGW bin directory, e.g. /c/Qt/Qt5.12.6/Tools/mingw730_32/bin" >&2
  return 1 2>/dev/null || exit 1
fi

if [[ -z "$CC_BIN" || -z "$CXX_BIN" || -z "$AR_BIN" ]]; then
  echo "Error: gcc/g++/ar not fully available in PATH." >&2
  echo "Set --mingw-bin to your MinGW bin directory, e.g. /c/Qt/Qt5.12.6/Tools/mingw730_32/bin" >&2
  return 1 2>/dev/null || exit 1
fi

echo "Detected make program: $MAKE_PROGRAM"
echo "Detected C compiler: $CC_BIN"
echo "Detected CXX compiler: $CXX_BIN"

export CC="gcc"
export CXX="g++"
export AR="ar"

if [[ "$CONFIGURE_AND_BUILD" -ne 1 ]]; then
  echo "Environment variables were set only for this terminal session."

  echo "Running CMake configure in $BUILD_DIR (cmake ..)"
  mkdir -p "$BUILD_DIR"
  (
    cd "$BUILD_DIR"
    rm -f CMakeCache.txt
    cmake .. -G "MSYS Makefiles" \
      -DCMAKE_MAKE_PROGRAM="$MAKE_PROGRAM"
  )

  if [[ "$IS_SOURCED" -ne 1 ]]; then
    cd "$BUILD_DIR"
    echo "Opened build shell in: $(pwd)"
    echo "CMake configure finished. You can run: cmake --build . --target $TARGET --parallel $JOBS"
    exec bash -i
  fi

  echo "Configure finished. Run build manually when needed:"
  echo "  cmake --build $BUILD_DIR --target $TARGET --parallel $JOBS"
  return 0 2>/dev/null || exit 0
fi

echo "Configuring project with generator: $CMAKE_GENERATOR"
cmake -S "$SOURCE_DIR" -B "$BUILD_DIR" -G "MSYS Makefiles" \
  -DCMAKE_MAKE_PROGRAM="$MAKE_PROGRAM"

echo "Building target: $TARGET"
cmake --build "$BUILD_DIR" --target "$TARGET" --parallel "$JOBS"

if [[ "$IS_SOURCED" -ne 1 ]]; then
  echo "Note: script was not sourced; env changes applied only to this command run."
fi
