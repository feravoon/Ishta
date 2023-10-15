#include "Camera.h"

Ray Camera::getRayAtPixel(float x, float y)
{
    float horPixelAngle = this->angles.x + (x - resolution.x/2 - 0.5f) * this->fov.x / this->resolution.x;
    float verPixelAngle = this->angles.y - (y - resolution.y/2 - 0.5f) * this->fov.y / this->resolution.y;
    float horAngle = cosf(this->angles.z)*horPixelAngle + sinf(this->angles.z)*verPixelAngle;
    float verAngle = sinf(this->angles.z)*horPixelAngle + cosf(this->angles.z)*verPixelAngle;

    return Ray(this->position,glm::vec2(horAngle, verAngle));
}

Camera::Camera(glm::vec3 position, glm::vec3 angles, glm::vec2 resolution, glm::vec2 fov)
{
    this->position = position;
    this->angles = angles;
    this->resolution = resolution;
    this->fov = fov;
}

Camera::Camera()
{
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->angles = glm::vec3(0.0f, 0.0f, 0.0f);
    this->resolution = glm::vec2(640,480);
    this->fov = glm::vec2(DEG2RAD(32),DEG2RAD(24));
}
