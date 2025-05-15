set(CMAKE_TOOLCHAIN_FILE /opt/devkitpro/cmake/WiiU.cmake)

include_directories("libraries/WiiU")
include("/opt/devkitpro/portlibs/wiiu/share/romfs-wiiu.cmake" REQUIRED)
add_compile_definitions(TP_WIIU)