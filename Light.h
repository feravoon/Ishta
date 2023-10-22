#pragma once
#include "glm/vec3.hpp"

class Light {

    public:
        glm::vec3 position;
        glm::vec3 color;
        float intensity;
        Light();
        Light(glm::vec3 position, glm::vec3 color, float intensity);
        Light(float posx, float posy, float posz);
        Light(float posx, float posy, float posz, float colorx, float colory, float colorz, float intensity);
};