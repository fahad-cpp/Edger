if exist Edger.exe del Edger.exe
if not exist bin mkdir bin
g++ src/*.cpp src/*.h -o bin/Edger.exe
start bin/Edger.exe