import argparse
import os

parser = argparse.ArgumentParser()
parser.add_argument("platform", help="The platform you want to build for")
parser.add_argument("-ts", "--twoscreen", help="Enables dual screen mode. Only works on some platforms.", action="store_true")
args = parser.parse_args()


compileDefines = []



if args.platform == "windows":
    compileDefines.append("PLATFORM_WINDOWS=true")
    compileDefines.append("CMAKE_BUILD_TYPE=Release")
    compileDefines.append("DEBUG=true")
elif args.platform == "wiiu":
    compileDefines.append("PLATFORM_WIIU=true")

stringargs = ""
for arg in compileDefines:
    stringargs += "-D" + arg + " "


os.system("cmake -S. -Bbuild " + stringargs)
os.system("cmake --build build")