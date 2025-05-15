target_link_libraries(CrossShift2 glfw glm)

set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/build/libraries/Windows/ffmpeg/lib/pkgconfig")
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
    libavdevice
    libavfilter
    libavformat
    libavcodec
    libswresample
    libswscale
    libavutil
)
target_include_directories(CrossShift2 PRIVATE build/libraries/Windows/ffmpeg/include)
target_link_libraries(CrossShift2 PkgConfig::LIBAV)