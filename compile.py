import argparse
import importlib
import os
import shutil


# Parse Args
os.system("cls")
os.system("clear")
parser = argparse.ArgumentParser()
parser.add_argument("platform", help="The platform you want to build for")
parser.add_argument("--twoscreen", help="Enables dual screen mode. Only works on some platforms.", action="store_true")
parser.add_argument("--rebuild_assets", "-ra", help="Force rebuilds the asset registry.", action="store_true")
parser.add_argument("--launch_after_compile", "--launch-after-compile", help="Launches the game after compiling", action="store_true")
args = parser.parse_args()

compileDefines = []

# Add every compile define in buildinfo/platform/compiledefines.txt
with open("buildinfo/" + args.platform + "/compile_defines.txt", "r") as compileDefinesFile:
    for line in compileDefinesFile:
        compileDefines.append(line.replace("\n",""))
# Stringify these args
stringargs = ""
for arg in compileDefines:
    stringargs += "-D" + arg + " "

commands = []
# Add CMAKE commands
commands.append("cmake -S.  -Bbuild/" + args.platform + " "  + stringargs)
commands.append("cmake --build build/" + args.platform)
# Launch after compile
if args.launch_after_compile :
    commands.append(open("buildinfo/" + args.platform + "/launch_after_compile.txt", "r").readline())

# Setup assets folder
builtAssetPath = "build/" + args.platform + "/assets"
if not os.path.exists(builtAssetPath):
    os.mkdir(builtAssetPath)
elif args.rebuild_assets:
    shutil.rmtree(builtAssetPath)
# Check assets
def copyFile(sourcePath, buildPath):
    if not os.path.exists(os.path.dirname(buildPath)):
        os.mkdir(os.path.dirname(buildPath))

    root, ext = os.path.splitext(sourcePath)
    if os.path.exists("buildinfo/assetparsers/" + ext[1:] + ".py"):
        module = importlib.import_module("buildinfo.assetparsers." + ext[1:])
        module.parse_and_copy(sourcePath, buildPath)
    else:
        shutil.copy(sourcePath, buildPath)



for subdir, dirs, files in os.walk("assets"):
    for file in files:
        buildPath = os.path.join(subdir, file).replace("assets", builtAssetPath).replace("\\","/")
        sourcePath = os.path.join(subdir, file).replace("\\","/")
        if not os.path.exists(buildPath):
            copyFile(sourcePath, buildPath)
            continue
        if os.path.getmtime(sourcePath) > os.path.getmtime(buildPath):
            copyFile(sourcePath,buildPath)
            continue
        if args.rebuild_assets:
            copyFile(sourcePath, buildPath)
            continue




# Execute all commands
with open("lastBuildCommand.sh", "w") as cmds:
    for command in commands:
        cmds.write(command + "\n")
        os.system(command)