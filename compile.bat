@echo off
echo [Compile.bat] Deleting old executable...
del build\game.exe
echo [Compile.bat] Compiling game...
g++ -g src/*.cpp -o build/game.exe -Iinclude -Isdk/sdl2/include -Lsdk/sdl2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
echo [Compile.bat] Running game...

build\game.exe