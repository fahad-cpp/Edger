@echo off
setlocal
if exist Edger.exe del Edger.exe
if not exist bin mkdir bin


where cmake >nul 2>nul
if errorlevel 1 (
    echo cmake not found
    exit /b 1
)
echo compiling using cmake...
goto compileCmake

where g++ >nul 2>nul
if errorlevel 1 (
    echo g++ compiler not found
    exit /b 1
)
echo compiling using g++...
goto compilegcc

:compilegcc
g++ -O3 -DNDEBUG -D_NDEBUG src/*.cpp src/*.h -o bin/Edger.exe
if errorlevel 1 (
    echo compilation failed.
    exit /b 1
)
goto startProgram

:compileCmake
if not exist build mkdir build
pushd build
cmake -S .. -DCMAKE_BUILD_TYPE=Release >nul 2>error.txt
if errorlevel 1 (
    type error.txt
    exit /b 1
)

cmake --build . --config Release --parallel >error.txt 2>nul
if errorlevel 1 (
    type error.txt
    exit /b 1
)
popd
goto startProgram

:startProgram
start bin/Edger.exe

endlocal