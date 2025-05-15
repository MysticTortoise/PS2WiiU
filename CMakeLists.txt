cmake_minimum_required(VERSION 3.24)
project(CrossShift2 CXX C)

message("Building for ${PLATFORM}...")

if(DEBUG)
   add_compile_definitions(TP_DEBUG)
endif(DEBUG)

include(buildinfo/${PLATFORM}/pre_app.cmake)

add_subdirectory(libraries/Common/glm)
add_subdirectory(libraries/Common/fpm)

file(GLOB_RECURSE sources source/*.cpp source/*.c)
file(GLOB_RECURSE includes include/*.h include/*.hpp)

add_executable(CrossShift2
   ${sources} ${includes} ${libsources})

if(DEBUG)
   set_property(TARGET CrossShift2 PROPERTY INTERPROCEDURAL_OPTIMIZATION FALSE)
endif(DEBUG)

target_include_directories(CrossShift2 PRIVATE 
   include 
   include/Platform
   libraries/Common/glm
   libraries/Common/fpm/include
   )

target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

include(buildinfo/${PLATFORM}/post_app.cmake)
