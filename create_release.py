import sys, os


def create_dir(directory):
    if not os.path.exists(directory):
        os.system("mkdir " + directory)


def create_build_dir(project_directory):
    build_directory = (project_directory + "/build")
    create_dir(build_directory)


def build_project(project_directory):
    create_build_dir(project_directory)
    os.system('cd ' + project_directory +'/build && cmake ../ -G "MSYS Makefiles" && make -j4 app && cd ..')


def remove_file_or_directory_if_exist(direcotry):
    if os.path.exists(direcotry):
        os.system("rm -rf " + direcotry)


def clear_build_dir(build_directory):
    remove_file_or_directory_if_exist(build_directory + "/CMakeFiles")
    remove_file_or_directory_if_exist(build_directory + "/galacticwar_autogen")
    remove_file_or_directory_if_exist(build_directory + "/images/*.gal")
    remove_file_or_directory_if_exist(build_directory + "/*.cmake")
    remove_file_or_directory_if_exist(build_directory + "/Makefile")


def collect_all_dependancy(build_directory):
    os.system("windeployqt.exe "+ build_directory + "/galacticwar.exe --release --no-translations")


def open_file(file_path, mode = "r"):
    if os.path.exists(file_path):
        try:
            file = open(file_path, mode)
            return file
        except:
            raise
    else:
        print(file_path + " doesn't exist or wring file path")
        exit()


def create_release_dir(project_directory):
    release_directory = (project_directory + "/release")
    create_dir(release_directory)


def change_release_version_in_inno_setup_script(project_directory, release_version):
    inno_setup_script = open_file(project_directory + "/galacticwarsetup.iss", "r+")
    new_release_version_line = ('#define MyAppVersion "' + release_version + '"\n')
    version_string_key = "#define MyAppVersion"
    output_new_inno_setup_script_content = []

    for line in inno_setup_script:
        if version_string_key in line:
            line = new_release_version_line
        output_new_inno_setup_script_content.append(line)

    inno_setup_script.seek(0)
    inno_setup_script.truncate()
    inno_setup_script.writelines(output_new_inno_setup_script_content)


def run_inno_setup_script(project_directory):
    os.system("ISCC.exe " + project_directory + "/galacticwarsetup.iss")


def create_release(project_directory, release_version):
#    build_project(project_directory)

    build_directory = (project_directory + "/build/app")
    clear_build_dir(build_directory)
    collect_all_dependancy(build_directory)

    create_release_dir(project_directory)
    change_release_version_in_inno_setup_script(project_directory, release_version)
    run_inno_setup_script(project_directory)


VALID_NUM_OF_ARGS = 2

def main():
    input_args = sys.argv[1:]

    if len(input_args) == VALID_NUM_OF_ARGS:
        project_directory = input_args[0]
        release_version = input_args[1]

        create_release(
            project_directory,
            release_version
        )
    else:
        print("Wrong input arguments")

main()

