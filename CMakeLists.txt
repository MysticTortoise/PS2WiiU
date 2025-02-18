cmake_minimum_required(VERSION 3.10)
project(CrossShift2 CXX)

if(DEBUG)
   add_compile_definitions(TP_DEBUG)
endif(DEBUG)

if(PLATFORM_WINDOWS)
   # Fetch GLFW and GLAD

   include(FetchContent)
   FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG master)
   FetchContent_Declare(glad GIT_REPOSITORY https://github.com/SasLuca/MyGlad.git GIT_TAG master)

   set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
   set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
   set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
   FetchContent_MakeAvailable(glfw)
   FetchContent_MakeAvailable(glad)

   add_compile_definitions(TP_WIN)
endif(PLATFORM_WINDOWS)

if(PLATFORM_WIIU)
   set(CMAKE_TOOLCHAIN_FILE /opt/devkitpro/cmake/WiiU.cmake)
endif(PLATFORM_WIIU)

file(GLOB_RECURSE sources source/*.cpp source/*.c)
file(GLOB_RECURSE includes include/*.h include/*.hpp)

add_executable(CrossShift2
   ${sources} ${includes})

target_include_directories(CrossShift2 PRIVATE include)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

if(PLATFORM_WINDOWS)
   target_link_libraries(CrossShift2 glad glfw)
endif(PLATFORM_WINDOWS)

if(PLATFORM_WIIU)
   wut_create_rpx(CrossShift2)
endif(PLATFORM_WIIU)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/crossshift2.rpx"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")