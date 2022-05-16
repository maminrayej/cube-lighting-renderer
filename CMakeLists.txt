cmake_minimum_required(VERSION 3.21)

project(Lighting
        VERSION 0.1
        DESCRIPTION "Learning Lighting"
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lighting
        src/main.cpp
        include/shader_program.h include/shader_program.inl
        include/shader_helper.h src/shader_helper.cpp
        include/io.h src/io.cpp
        include/camera.h src/camera.cpp)

target_include_directories(Lighting PUBLIC include)

# Statically link everything
#set(CMAKE_EXE_LINKER_FLAGS " -static")

# --- GLFW Configuration
# Disable building docs, tests and examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw-3.3.6)

target_link_libraries(Lighting PRIVATE glfw)

# --- GLAD Configuration
add_subdirectory(lib/glad)

target_link_libraries(Lighting PRIVATE glad)

# --- GLM Configuration
add_subdirectory(lib/glm)

target_link_libraries(Lighting PRIVATE glm)