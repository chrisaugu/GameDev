; -- Example1.iss --
; Demonstrates copying 3 files and creating an icon.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]
AppName=PingPong
AppVersion=1.5
WizardStyle=modern
DefaultDirName={autopf}\PingPong
DefaultGroupName=PingPong
UninstallDisplayIcon={app}\PingPong.exe
Compression=lzma2
SolidCompression=yes
OutputDir=userdocs:Inno Setup Examples Output

[Files]
Source: "bin/Debug/PingPong.exe"; DestDir: "{app}"
Source: "bin/Debug/SDL2.dll"; DestDir: "{app}"
Source: "Readme.txt"; DestDir: "{app}"; Flags: isreadme

[Icons]
Name: "{group}\PingPong"; Filename: "{app}\PingPong.exe"
