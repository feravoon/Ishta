#pragma once
#include "Ray.h"
#include "Plane.h"
#include "Light.h"
#include <vector>
struct RaySample
{
    float depth;
    glm::vec3 colorIntensity;
    glm::vec3 intersection;
};

class RayTracer {
    public:
        static RaySample sampleRay(Ray &ray, std::vector<Plane> &planeSet, std::vector<Light> &lightSet);
};