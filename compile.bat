@echo off
set /p platform=Platform: 

if %platform%==wiiu (
    C:\devkitPro\msys2\usr\bin\env MSYSTEM=MSYS /usr/bin/bash -lc /d/Programming/PS2WiiU/compilewiiu.sh
)
if %platform%==windows (
    cmake -S. -Bbuild -DPLATFORM_WINDOWS=true -DCMAKE_BUILD_TYPE=Release
    cmake --build build
)

pause