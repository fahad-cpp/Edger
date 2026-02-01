@echo off
setlocal
if exist bin\Edger.exe del bin\Edger.exe
if not exist bin mkdir bin

REM first try g++
where g++ >nul 2>nul
if errorlevel 1 (
    echo g++ compiler not found
    goto tryCMake
)
echo compiling using g++...
goto compilegcc

REM if g++ does not work try CMake
:tryCMake
where cmake >nul 2>nul
if errorlevel 1 (
    echo cmake not found
    exit /b 1
)
echo compiling using cmake...
goto compileCmake

REM compile using g++
:compilegcc
g++ -O3 -DNDEBUG -D_NDEBUG src/*.cpp src/*.h -o bin/Edger.exe
if errorlevel 1 (
    echo compilation failed.
    exit /b 1
)
goto startProgram

REM compile using CMake
:compileCmake
if not exist build mkdir build
pushd build
cmake -S .. -DCMAKE_BUILD_TYPE=Release >nul 2>error.txt
if errorlevel 1 (
    echo failed to generate build files using cmake.
    type error.txt
    exit /b 1
)

cmake --build . --config Release --parallel >error.txt 2>nul
if errorlevel 1 (
    echo failed to build the program.
    type error.txt
    exit /b 1
)
popd
goto startProgram

:startProgram
echo successfully compiled.
start bin/Edger.exe

endlocal