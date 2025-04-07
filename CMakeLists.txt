cmake_minimum_required(VERSION 3.24)
project(CrossShift2)

if(DEBUG)
   add_compile_definitions(TP_DEBUG)
endif(DEBUG)

if(PLATFORM_WINDOWS)
   add_subdirectory(libraries/windows/glfw/)
   include_directories(SYSTEM "libraries/windows/GLAD/include")
   include_directories(SYSTEM "libraries/build/Windows/ffmpeg/include")
   set(libsources "libraries/windows/GLAD/src/glad.c")

   add_compile_definitions(TP_WIN)
   set(BUILT_LIBS_DIR ${CMAKE_SOURCE_DIR}/libraries/build/Windows)

endif(PLATFORM_WINDOWS)

if(PLATFORM_WIIU)
   set(CMAKE_TOOLCHAIN_FILE /opt/devkitpro/cmake/WiiU.cmake)

   include_directories("libraries/WiiU")
   include_directories(SYSTEM "libraries/build/WiiU/ffmpeg/include")

   include("/opt/devkitpro/portlibs/wiiu/share/romfs-wiiu.cmake" REQUIRED)
   add_compile_definitions(TP_WIIU)
   set(BUILT_LIBS_DIR ${CMAKE_SOURCE_DIR}/libraries/build/wiiu)
endif(PLATFORM_WIIU)



add_subdirectory(libraries/Common/glm)

file(GLOB_RECURSE sources source/*.cpp source/*.c)
file(GLOB_RECURSE includes include/*.h include/*.hpp)

add_executable(CrossShift2
   ${sources} ${includes} ${libsources})


target_include_directories(CrossShift2 PRIVATE 
   include 
   include/Platform
   libraries/Common/glm
   )


# FFMPEG
set(ENV{PKG_CONFIG_PATH} "${BUILT_LIBS_DIR}/ffmpeg/lib/pkgconfig")
find_package(PkgConfig REQUIRED)



target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

if(PLATFORM_WINDOWS)
   pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
      libavdevice
      libavfilter
      libavformat
      libavcodec
      libswresample
      libswscale
      libavutil
   )
   #message(${LIBAV_LINK_LIBRARIES})

   target_link_libraries(CrossShift2 PkgConfig::LIBAV)

   target_include_directories(CrossShift2 PRIVATE
   libraries/Windows/FFmpeg/include
   )

   target_link_libraries(CrossShift2 
   glfw
   glm
   )
endif(PLATFORM_WINDOWS)

if(PLATFORM_WIIU)
   romfs_add(CrossShift2 "assets")

   wut_create_rpx(CrossShift2)
   install(FILES "${CMAKE_CURRENT_BINARY_DIR}/crossshift2.rpx"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif(PLATFORM_WIIU)