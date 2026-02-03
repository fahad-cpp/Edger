@echo off
setlocal
set BASEDIR=%~dp0
set SHORTCUT=%BASEDIR%\Edger.lnk
set STARTIN=%BASEDIR%
set ICON=%BASEDIR%\icon.ico
set EXE=%BASEDIR%\bin\Edger.exe

if exist %SHORTCUT% del %SHORTCUT%

if not exist %EXE% (
    echo Executable does not exist.
    exit /b 1
)

powershell "$s=(New-Object -COM WScript.Shell).CreateShortCut('%SHORTCUT%');$s.TargetPath='%EXE%';$s.WorkingDirectory='%STARTIN%';$s.IconLocation='%ICON%';$s.Save()"
endlocal
