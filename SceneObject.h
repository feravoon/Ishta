#pragma once
#include "Ray.h"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/common.hpp"
#include "glm/geometric.hpp"

class SceneObject {
    public:
        virtual glm::vec3 intersectWithRay(Ray &ray) = 0;
        virtual float angleBetweenSurfaceNormalAndRay(Ray &ray, glm::vec3 posOnSurface) = 0;
        virtual ~SceneObject() = 0;
};