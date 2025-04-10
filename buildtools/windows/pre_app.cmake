message("Building on Windows")

add_subdirectory(libraries/windows/glfw/)
include_directories(SYSTEM "libraries/windows/GLAD/include")
set(libsources "libraries/windows/GLAD/src/glad.c")

add_compile_definitions(TP_WIN)