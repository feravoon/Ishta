clang++ -Ofast -std=c++11 -o Program main.cpp Renderer.cpp Ray.cpp Plane.cpp Camera.cpp Light.cpp RayTracer.cpp -L/opt/homebrew/lib -lSDL2 -I/opt/homebrew/include -D_THREAD_SAFE -Wall -lm
