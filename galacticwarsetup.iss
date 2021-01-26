#define MyAppName "GalacticWar"
#define MyAppVersion "1.0.0"
#define MyAppPublisher "Tadeusz Biela (TED)"
#define MyAppURL "https://github.com/TadekBiela/GalacticWar"
#define MyAppExeName "galacticwar.exe"

[Setup]
AppId={{46BDC3DD-1420-430B-8E33-3202408C3381}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
DisableProgramGroupPage=yes
LicenseFile=C:\GameDev\GalacticWar\LICENSE.txt
PrivilegesRequiredOverridesAllowed=dialog
OutputDir=C:\GameDev\GalacticWar\release
OutputBaseFilename=galacticwarsetup
SetupIconFile=C:\GameDev\GalacticWar\app\images\icon.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "C:\GameDev\GalacticWar\build\app\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\GameDev\GalacticWar\build\app\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
