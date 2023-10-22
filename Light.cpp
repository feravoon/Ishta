#include "Light.h"

Light::Light(){
    position = glm::vec3(0.0f, 0.0f, 0.0f); 
    color = glm::vec3(1.0f, 1.0f, 1.0f); // White
    intensity = 1.0f;
}

Light::Light(glm::vec3 position, glm::vec3 color, float intensity)
{
    this->position = position; 
    this->color = color;
    this->intensity = intensity;
}

Light::Light(float posx, float posy, float posz)
{
    position = glm::vec3(posx, posy, posz); 
    color = glm::vec3(1.0f, 1.0f, 1.0f); // White
    intensity = 1.0f;
}

Light::Light(float posx, float posy, float posz, float colorx, float colory, float colorz, float intensity)
{
    position = glm::vec3(posx, posy, posz); 
    color = glm::vec3(colorx, colory, colorz); // White
    this->intensity = intensity;
}
