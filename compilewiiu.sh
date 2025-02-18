SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

cd ${SCRIPT_DIR}
cmake -S. -Bbuild -DPLATFORM_WIIU=true -DCMAKE_BUILD_TYPE=Release
cmake --build build