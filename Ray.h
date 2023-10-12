#pragma once
#include "Plane.h"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/common.hpp"
#include <math.h>
#define DEG2RAD(x) M_PI*(x)/180.0f
#define RAD2DEG(x) (x)*180.0f/M_PI

class Ray {
    public:
      glm::vec3 initPoint, unitVector;
      glm::vec3 getPosAtRange(float range);
      glm::vec3 intersectWithPlane(Plane plane);
      float angleToNormalOfPlane(Plane plane);
      Ray(glm::vec3 initPoint, glm::vec2 angles);
      Ray(glm::vec3 initPoint, glm::vec3 unitVector);
      Ray();
};