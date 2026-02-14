#include "RayTracer.h"

RaySample RayTracer::sampleRay(Ray &ray, std::vector<std::shared_ptr<SceneObject>> &sceneObjectSet, std::vector<Light> &lightSet)
{
    // Check intersection with every object in the scene
    IntersectionData intersectionResult;
    intersectionResult = getClosestIntersection(ray, sceneObjectSet);

    RaySample rs;
    rs.colorIntensity = glm::vec3(0.0f);
    rs.depth = intersectionResult.minDepth;
    rs.intersection = intersectionResult.closestIntersection;
    rs.closestObjectIndex = intersectionResult.minDepthIndex;

    if(rs.closestObjectIndex == -1)
        return rs;

    glm::vec3 incomingLightVec;
    float distanceToLight;
    glm::vec3 diffuseColor = sceneObjectSet[intersectionResult.minDepthIndex]->material.diffuse;
    IntersectionData lightIntersectionResult;
    
    for(int i = 0; i < lightSet.size(); i++)
    {
        incomingLightVec = intersectionResult.closestIntersection - lightSet[i].position;
        distanceToLight = glm::length(incomingLightVec);
        incomingLightVec = incomingLightVec/distanceToLight; // normalization

        Ray lightRay(lightSet[i].position, incomingLightVec); // Create a ray of light
        
        // Check if the intersection point is in the shadow (i.e. light ray intersects something closer, thus blocking the light)
        lightIntersectionResult = getClosestIntersection(lightRay, sceneObjectSet);
        if(glm::length(intersectionResult.closestIntersection - lightIntersectionResult.closestIntersection)>0.1f)
            continue;

        float angleBetweenSurfaceNormalAndRay = sceneObjectSet[intersectionResult.minDepthIndex]->angleBetweenSurfaceNormalAndRay(lightRay, intersectionResult.closestIntersection) + M_PI;
        float reflectionCoeff = cosf(angleBetweenSurfaceNormalAndRay); // Lambertian model
        
        // Add the reflected color intensity from this light to total intensity
        rs.colorIntensity += diffuseColor * lightSet[i].color * lightSet[i].intensity * reflectionCoeff / (distanceToLight*distanceToLight);
        
    }
    rs.diffuseRef = diffuseColor;
    return rs;
}

RaySample RayTracer::recursiveSampleRay(Ray &ray, std::vector<std::shared_ptr<SceneObject>> &sceneObjectSet, std::vector<Light> &lightSet, uint32_t jumpsLeft)
{
    RaySample rs = sampleRay(ray, sceneObjectSet, lightSet);
    glm::vec3 colorIntensity = rs.colorIntensity;
    glm::vec3 diffuseRef = rs.diffuseRef;

    if(rs.closestObjectIndex!=-1 & jumpsLeft>0)
    {
        Ray secondRay = sceneObjectSet[rs.closestObjectIndex]->getReflectedRay(ray, rs.intersection);
        rs = recursiveSampleRay(secondRay,sceneObjectSet,lightSet,jumpsLeft-1);
        rs.colorIntensity = colorIntensity + 0.5f*rs.colorIntensity;//*diffuseRef;
    }

    return rs;
}

IntersectionData RayTracer::getClosestIntersection(Ray &ray, std::vector<std::shared_ptr<SceneObject>> &sceneObjectSet)
{
    IntersectionData result;
    result.minDepth = MAXFLOAT;
    result.minDepthIndex = -1;
    glm::vec3 intersection;
    float curDepth;

    for(int p = 0; p < sceneObjectSet.size(); p++)
    {
        intersection = sceneObjectSet[p]->intersectWithRay(ray);
        curDepth = glm::length(intersection - ray.initPoint);
        if(curDepth < result.minDepth)
        {
            result.minDepth = curDepth;
            result.minDepthIndex = p;
            result.closestIntersection = intersection;
        }
    }

    return result;
}
