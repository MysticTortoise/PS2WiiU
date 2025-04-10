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

with open("buildtools/" + args.platform + "/compile_defines.txt", "r") as compileDefinesFile:
    for line in compileDefinesFile:
        compileDefines.append(line.replace("\n",""))

stringargs = ""
for arg in compileDefines:
    stringargs += "-D" + arg + " "

commands = []

commands.append("cmake -S.  -Bbuild/" + args.platform + " "  + stringargs)
commands.append("cmake --build build/" + args.platform)

if args.launch_after_compile :
    commands.append(open("buildtools/" + args.platform + "/launch_after_compile.txt", "r").readline())

with open("lastBuildCommand.sh", "w") as cmds:
    for command in commands:
        cmds.write(command + "\n")
        os.system(command)