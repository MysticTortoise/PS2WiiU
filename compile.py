import argparse
import os
import subprocess



os.system("cls")
os.system("clear")
parser = argparse.ArgumentParser()
parser.add_argument("platform", help="The platform you want to build for")
parser.add_argument("--twoscreen", help="Enables dual screen mode. Only works on some platforms.", action="store_true")
parser.add_argument("--launch_after_compile", help="Launches the game after compiling", action="store_true")
args = parser.parse_args()

compileDefines = []

if args.platform == "windows":
    compileDefines.append("PLATFORM_WINDOWS=true")
    compileDefines.append("CMAKE_BUILD_TYPE=Release")
    compileDefines.append("DEBUG=true")
elif args.platform == "wiiu":
    compileDefines.append("PLATFORM_WIIU=true")
    compileDefines.append("CMAKE_TOOLCHAIN_FILE=/opt/devkitPro/cmake/WiiU.cmake")
    compileDefines.append("CMAKE_BUILD_TYPE=Release")
    compileDefines.append("CMAKE_C_COMPILER=/opt/devkitPro/devkitPPC/bin/powerpc-eabi-gcc.exe")
    compileDefines.append("CMAKE_CXX_COMPILER=/opt/devkitPro/devkitPPC/bin/powerpc-eabi-g++.exe")
    compileDefines.append("DEBUG=true")

stringargs = ""
for arg in compileDefines:
    stringargs += "-D" + arg + " "

os.system("cmake -S.  -Bbuild/" + args.platform + " "  + stringargs)
os.system("cmake --build build/" + args.platform)

if args.launch_after_compile :
    if args.platform == "windows":
        subprocess.run("build\\windows\\CrossShift2.exe")
    elif args.platform == "wiiu":
        subprocess.run("D:\\Downloads\Cemu_2.0-36/Cemu.exe -g \"D:\\Programming\\PS2WiiU\\build\\wiiu\\CrossShift2.rpx\"")
#D:\Downloads\Cemu_2.0-36\Cemu.exe -g "C:\Users\Denis\OneDrive\Documents\WIIU\GFX2\wii-u-random-junk\hypergfx2test.rpx"