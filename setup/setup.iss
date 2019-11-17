#define MyAppName 		"LaTeX Editor"
#define MyAppVersion 	"1.0"
#define MyAppPublisher 	"Corky Maigre"
#define MyAppURL 		"http://www.corkymaigre.be/"
#define MyAppExeName 	"tb3epb.exe"

[Setup]
AppId					={{638D4B2A-393C-404D-A54A-35649C158FA0}
AppName					={#MyAppName}
AppVersion				={#MyAppVersion}
;AppVerName				={#MyAppName} {#MyAppVersion}
AppPublisher			={#MyAppPublisher}
AppPublisherURL			={#MyAppURL}
AppSupportURL			={#MyAppURL}
AppUpdatesURL			={#MyAppURL}
DefaultDirName			={pf}\{#MyAppName}
DefaultGroupName		={#MyAppName}
AllowNoIcons			=yes
LicenseFile				=C:\Users\maico\Documents\tb3epb\deployment\license.txt
OutputDir				=C:\Users\maico\Documents\tb3epb\distribution
OutputBaseFilename		=setup
SetupIconFile			=C:\Users\maico\Documents\tb3epb\deployment\icon.ico
Compression				=lzma
SolidCompression		=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "C:\Users\maico\Documents\tb3epb\deployment\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

