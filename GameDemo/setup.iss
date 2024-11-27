; -- Example1.iss --
; Demonstrates copying 3 files and creating an icon.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]
AppName=GameDemo
AppVersion=1.5
WizardStyle=modern
DefaultDirName={autopf}\GameDemo
DefaultGroupName=GameDemo
UninstallDisplayIcon={app}\GameDemo.exe
Compression=lzma2
SolidCompression=yes
OutputDir=userdocs:Inno Setup Examples Output

[Files]
Source: "bin/Debug/GameDemo.exe"; DestDir: "{app}"
Source: "bin/Debug/SDL2.dll"; DestDir: "{app}"
Source: "Readme.txt"; DestDir: "{app}"; Flags: isreadme

[Icons]
Name: "{group}\GameDemo"; Filename: "{app}\GameDemo.exe"
