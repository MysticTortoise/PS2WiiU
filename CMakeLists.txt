cmake_minimum_required(VERSION 3.24)
project(CrossShift2 CXX C)

if(DEBUG)
   add_compile_definitions(TP_DEBUG)
endif(DEBUG)

if(PLATFORM_WINDOWS)
   add_subdirectory(libraries/windows/glfw/)
   include_directories(SYSTEM "libraries/windows/GLAD/include")
   set(libsources "libraries/windows/GLAD/src/glad.c")

   add_compile_definitions(TP_WIN)
endif(PLATFORM_WINDOWS)

if(PLATFORM_WIIU)
   set(CMAKE_TOOLCHAIN_FILE /opt/devkitpro/cmake/WiiU.cmake)

   include_directories("libraries/WiiU")
   include("/opt/devkitpro/portlibs/wiiu/share/romfs-wiiu.cmake" REQUIRED)
   add_compile_definitions(TP_WIIU)
endif(PLATFORM_WIIU)

add_subdirectory(libraries/common/glm)

file(GLOB_RECURSE sources source/*.cpp source/*.c)
file(GLOB_RECURSE includes include/*.h include/*.hpp)

add_executable(CrossShift2
   ${sources} ${includes} ${libsources})

target_include_directories(CrossShift2 PRIVATE 
   include 
   include/Platform
   libraries/Common/glm
   )

target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

if(PLATFORM_WINDOWS)
   target_link_libraries(CrossShift2 glfw glm)
endif(PLATFORM_WINDOWS)

if(PLATFORM_WIIU)
   romfs_add(CrossShift2 "assets")

   wut_create_rpx(CrossShift2)
   install(FILES "${CMAKE_CURRENT_BINARY_DIR}/crossshift2.rpx"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif(PLATFORM_WIIU)

