#!/bin/sh
SOURCES="main.cpp Renderer.cpp Ray.cpp Plane.cpp Sphere.cpp Camera.cpp Light.cpp RayTracer.cpp SceneObject.cpp Material.cpp"
INCLUDE_PATH="/opt/homebrew/include"
LIBRARY_PATH="/opt/homebrew/lib"
LIBRARIES="-lSDL2"
EXECUTABLE="Program"
FLAGS="-Ofast -std=c++11 -D_THREAD_SAFE -Wall -lm"

g++ $FLAGS -o $EXECUTABLE $SOURCES -L$LIBRARY_PATH -I$INCLUDE_PATH $LIBRARIES
