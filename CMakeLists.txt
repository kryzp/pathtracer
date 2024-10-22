cmake_minimum_required(VERSION 3.28)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)

find_package(glm REQUIRED)

add_executable(${PROJECT_NAME}
	src/types.cpp
	src/main.cpp
	src/pathtracer.cpp
	src/world.cpp
	src/sphere.cpp
	src/plane.cpp
	src/camera.cpp
	src/texture.cpp
	src/material.cpp
)

target_link_libraries(${PROJECT_NAME} glm::glm)
