cmake -S.  -Bbuild/wiiu -DPLATFORM_WIIU=true -DCMAKE_TOOLCHAIN_FILE=/opt/devkitPro/cmake/WiiU.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=/opt/devkitPro/devkitPPC/bin/powerpc-eabi-gcc.exe -DCMAKE_CXX_COMPILER=/opt/devkitPro/devkitPPC/bin/powerpc-eabi-g++.exe -DDEBUG=true 
cmake --build build/wiiu
D:\Downloads\Cemu_2.0-36/Cemu.exe -g "D:\Programming\PS2WiiU\build\wiiu\CrossShift2.rpx"
