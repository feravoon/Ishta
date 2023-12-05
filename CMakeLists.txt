cmake_minimum_required(VERSION 3.1)

project(IshTa VERSION 1.0 DESCRIPTION "A simple ray tracer." LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -std=c++11 -D_THREAD_SAFE -Wall")

add_library(mainLib STATIC Renderer.cpp Ray.cpp Plane.cpp Sphere.cpp Camera.cpp Light.cpp RayTracer.cpp SceneObject.cpp Material.cpp)

target_link_libraries(mainLib -lSDL2)
target_link_libraries(mainLib -L/opt/homebrew/lib)

target_include_directories(mainLib PUBLIC /opt/homebrew/include)

add_executable(IshTaApp main.cpp)

target_link_libraries(IshTaApp mainLib)