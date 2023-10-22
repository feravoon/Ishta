#include "Ray.h"
#include "Plane.h"
#include "Camera.h"
#include "Renderer.h"
#include "Light.h"
#include "RayTracer.h"
#include <random>

int main()
{
    // Camera with a resolution of 640x480 and fov of 32 degrees by 24 degrees
    Camera cam;
    cam.position = glm::vec3(0.0f, -300.0f, 0.0f);
    cam.angles = glm::vec3(DEG2RAD(90.0f), DEG2RAD(0.0f), DEG2RAD(0.0f));
    cam.resolution = glm::vec2(640,480);
    cam.fov = glm::vec2(DEG2RAD(64),DEG2RAD(48));

    Light *lightSet[1];
    lightSet[0] = new Light(0.0f, 0.0f, 0.0f);
    lightSet[0]->intensity = 10000;
    lightSet[0]->color = 1.3f * glm::vec3(235/255.0f, 199/255.0f, 129/255.0f);

    Plane *planeSet[5];
    planeSet[0] = new Plane(0,0,1,100);
    planeSet[1] = new Plane(0,0,-1,100);
    planeSet[2] = new Plane(1,0,0,100);
    planeSet[3] = new Plane(-1,0,0,100);
    planeSet[4] = new Plane(0,-1,0,100);

    uint8_t image[cam.resolution.x*cam.resolution.y*3];

    Ray pixelRay;
    Ray secondRay;
    RaySample rs;    
    //RaySample rs2;

    glm::vec3 rawPixelVal;
    int ang = 0;
    float angRad = 0;

    //std::random_device rd;
    //std::mt19937 e2(rd());
    //std::uniform_real_distribution<> dist(-1, 1);

    Renderer renderer(1, cam.resolution.x, cam.resolution.y);
    int close = 0;
    SDL_Event event;
     while (!close) {
        // Events management
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                close = true;
                break;
            }
        }
        angRad = DEG2RAD(ang);
        //cam.angles.z = DEG2RAD(0.0f + 3*cosf(angRad));
        //cam.angles.x = DEG2RAD(90.0f + 3*sinf(angRad));
        ang+=10;
        if(ang>=360)
            ang = 0;

        lightSet[0]->position.x = 30*cosf(angRad);
        lightSet[0]->position.z = 30*sinf(angRad);

        for(int j=0; j<cam.resolution.y; j++)
        {
            for(int i=0; i<cam.resolution.x; i++)
            {
                pixelRay = cam.getRayAtPixel(i, j);
                rs = RayTracer::sampleRay(&pixelRay, planeSet, lightSet);
                //secondRay = Ray(rs.intersection,glm::vec3(dist(e2), dist(e2), dist(e2)));
                //rs2 = RayTracer::sampleRay(&secondRay, planeSet, lightSet);
                rawPixelVal = 255.0f * rs.colorIntensity / 2.0f; //+ 5000000*rs2.intensity/(rs.depth*rs.depth);

                rawPixelVal.r = glm::clamp(rawPixelVal.r,0.0f,255.0f);
                rawPixelVal.g = glm::clamp(rawPixelVal.g,0.0f,255.0f);
                rawPixelVal.b = glm::clamp(rawPixelVal.b,0.0f,255.0f);

                image[j*cam.resolution.x*3 + i*3]     = (uint8_t)(rawPixelVal.r);
                image[j*cam.resolution.x*3 + i*3 + 1] = (uint8_t)(rawPixelVal.g);
                image[j*cam.resolution.x*3 + i*3 + 2] = (uint8_t)(rawPixelVal.b);
            }
        }   
        renderer.render(image, cam.resolution.x, cam.resolution.y);
     }

    // destroy texture
    SDL_DestroyTexture(renderer.tex);
 
    // destroy renderer
    SDL_DestroyRenderer(renderer.rend);
 
    // destroy window
    SDL_DestroyWindow(renderer.win);

    // close SDL
    SDL_Quit();
    return 0;
}