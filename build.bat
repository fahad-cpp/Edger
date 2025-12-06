@echo off

setlocal
set "CONFIG=Release"
set "EXENAME=Edger.exe"

if not exist bin mkdir bin

::Check if cmake exists
where cmake >nul 2>nul
if errorlevel 1 (
    where g++ >nul 2>nul
    if errorlevel 1 (
        echo [build.bat]:No Compatible C++ build tools were found.
        exit /b 1
    )
    g++ src/*.cpp src/*.h -o bin/%EXENAME%
    goto run
)
:cmake
if not exist build mkdir build
pushd build
cmake .. >nul
if errorlevel 1 (
    echo [build.bat]:Error Generating build files
    exit /b 1
)
cmake --build . --config %CONFIG% --parallel >nul
if errorlevel 1 (
    echo [build.bat]:Error building project.
    exit /b 1
)
popd
goto run

:run
echo [build.bat]:Succesfully compiled to bin/%EXENAME%
start bin/%EXENAME%

endlocal