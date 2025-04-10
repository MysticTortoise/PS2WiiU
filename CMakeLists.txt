cmake_minimum_required(VERSION 3.24)
project(CrossShift2 CXX C)

if(DEBUG)
   add_compile_definitions(TP_DEBUG)
endif(DEBUG)

include(buildtools/${PLATFORM}/pre_app.cmake)

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

include(buildtools/${PLATFORM}/post_app.cmake)
