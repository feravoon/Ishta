#pragma once
#include "Ray.h"
#include "Plane.h"
#include "Light.h"
#include "Sphere.h"
#include "SceneObject.h"
#include <vector>
struct RaySample
{
    float depth;
    glm::vec3 colorIntensity;
    glm::vec3 intersection;
};

class RayTracer {
    public:
        static RaySample sampleRay(Ray &ray, std::vector<std::shared_ptr<SceneObject>> &sceneObjectSet, std::vector<Light> &lightSet);
};