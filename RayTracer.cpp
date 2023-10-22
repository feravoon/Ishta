#include "RayTracer.h"

RaySample RayTracer::sampleRay(Ray *ray, Plane **planeSet, Light **lightSet)
{
    glm::vec3 intersection, incomingLightVec;
    float curDepth;
    int minDepthIndex;
    float minDepth = MAXFLOAT;
    float distanceToLight;

    for(int p=0; p<5; p++)
    {
        intersection = ray->intersectWithPlane(*planeSet[p]);
        curDepth = glm::length(intersection - ray->initPoint);
        if(curDepth<minDepth)
        {
            minDepth = curDepth;
            minDepthIndex = p;
        }
    }
    
    intersection = ray->intersectWithPlane(*planeSet[minDepthIndex]);
    
    incomingLightVec = intersection - lightSet[0]->position;
    distanceToLight = glm::length(incomingLightVec);
    incomingLightVec = incomingLightVec/distanceToLight;

    Ray lightRay(lightSet[0]->position, incomingLightVec);

    RaySample rs;

    rs.colorIntensity = lightSet[0]->color * lightSet[0]->intensity * -(cosf(lightRay.angleToNormalOfPlane(*planeSet[minDepthIndex]))) / (distanceToLight*distanceToLight);
    rs.depth = minDepth;
    rs.intersection = intersection;

    return rs;
}