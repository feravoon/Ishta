#pragma once
#include "Ray.h"
#include "glm/vec2.hpp"

class Camera {
    public:
      glm::vec3 position;
      glm::vec3 angles; // yaw, pitch, roll
      glm::vec<2, unsigned int,glm::packed_highp> resolution;
      glm::vec2 fov;
      float exposure;
      Ray getRayAtPixel(float x, float y);
      Camera(glm::vec3 position, glm::vec3 angles, glm::vec2 resolution, glm::vec2 fov);
      Camera();
};