cmake_minimum_required(VERSION 3.24)
project(CrossShift2 CXX C)

if(DEBUG)
   add_compile_definitions(TP_DEBUG)
endif(DEBUG)

if(PLATFORM_WINDOWS)
   add_subdirectory(libraries/Windows/glfw/)
   include_directories(SYSTEM "libraries/Windows/GLAD/include")
   set(libsources "libraries/Windows/GLAD/src/glad.c")

   add_compile_definitions(TP_WIN)
endif(PLATFORM_WINDOWS)

if(PLATFORM_WIIU)
   set(CMAKE_TOOLCHAIN_FILE /opt/devkitpro/cmake/WiiU.cmake)
endif(PLATFORM_WIIU)

file(GLOB_RECURSE sources source/*.cpp source/*.c)
file(GLOB_RECURSE includes include/*.h include/*.hpp)

add_executable(CrossShift2
   ${sources} ${includes} ${libsources})

target_include_directories(CrossShift2 PRIVATE include)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

if(PLATFORM_WINDOWS)
   target_link_libraries(CrossShift2 glfw)
endif(PLATFORM_WINDOWS)

if(PLATFORM_WIIU)
   wut_create_rpx(CrossShift2)
   install(FILES "${CMAKE_CURRENT_BINARY_DIR}/crossshift2.rpx"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif(PLATFORM_WIIU)

