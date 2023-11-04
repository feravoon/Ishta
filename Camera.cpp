#include "Camera.h"

Ray Camera::getRayAtPixel(float x, float y)
{
    float fx = (resolution.x/2) / tanf(this->fov.x/2);
    float fy = (resolution.y/2) / tanf(this->fov.y/2);

    float horPixelAngle = atan2f(-(x - resolution.x/2 - 0.5f),fx);
    float verPixelAngle = atan2f(-(y - resolution.y/2 - 0.5f),fy);

    // Fish-eye projection
    //float horPixelAngle = this->angles.x + (x - resolution.x/2 - 0.5f) * this->fov.x / this->resolution.x;
    //float verPixelAngle = this->angles.y - (y - resolution.y/2 - 0.5f) * this->fov.y / this->resolution.y;
    
    float horAngle = this->angles.x + cosf(this->angles.z)*horPixelAngle + sinf(this->angles.z)*verPixelAngle;
    float verAngle = this->angles.y - sinf(this->angles.z)*horPixelAngle + cosf(this->angles.z)*verPixelAngle;

    return Ray(this->position,glm::vec2(horAngle, verAngle));
}

Camera::Camera(glm::vec3 position, glm::vec3 angles, glm::vec2 resolution, glm::vec2 fov)
{
    this->position = position;
    this->angles = angles;
    this->resolution = resolution;
    this->fov = fov;
    this->exposure = 1.0f;
}

Camera::Camera()
{
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->angles = glm::vec3(0.0f, 0.0f, 0.0f);
    this->resolution = glm::vec2(640,480);
    this->fov = glm::vec2(DEG2RAD(32),DEG2RAD(24));
    this->exposure = 1.0f;
}
