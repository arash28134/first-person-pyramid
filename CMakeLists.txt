cmake_minimum_required(VERSION 3.13)  # CMake version check
project(first_person_pyramid)               # create project "first_person_pyramid"
set(CMAKE_CXX_STANDARD 14)            # enable c++14 standard

# add source files
set(SOURCE_FILES 
src/main.cpp 
src/window.cpp 
src/shader.cpp
src/shaders.cpp 
src/mesh.cpp
src/camera.cpp 
src/mesh_utils.cpp 
src/anim_utils.cpp
src/window_utils.cpp)

# add executable target with source files listed in SOURCE_FILES variable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# find packages
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

# link libraries
target_link_libraries(${PROJECT_NAME} glfw GLEW::glew ${OPENGL_LIBRARIES})

# include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)