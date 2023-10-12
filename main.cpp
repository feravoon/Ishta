#include "Ray.h"
#include "Plane.h"
#include "Camera.h"
#include "Renderer.h"

int main()
{
    // Camera with a resolution of 640x480 and fov of 32 degrees by 24 degrees
    Camera cam;
    cam.position = glm::vec3(0.0f, -200.0f, 0.0f);
    cam.angles = glm::vec3(DEG2RAD(91.0f), DEG2RAD(0.0f), DEG2RAD(0.0f));
    cam.resolution = glm::vec2(640,480);
    cam.fov = glm::vec2(DEG2RAD(32),DEG2RAD(24));

    Plane *planeSet[5];

    planeSet[0] = new Plane(0,0,1,-100);
    planeSet[1] = new Plane(0,0,-1,-100);
    planeSet[2] = new Plane(1,0,0,-100);
    planeSet[3] = new Plane(-1,0,0,-100);
    planeSet[4] = new Plane(0,-1,0,-1000);

    uint8_t image[cam.resolution.x*cam.resolution.y*3];

    Ray pixelRay;
    float curDepth; 
    float minDepth = 25000.0f;
    glm::vec3 intersection;
    float rawPixelVal;
    int ang = 0;
    float angRad = 0;

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
        //cam.angles = glm::vec3(DEG2RAD(90.0f + 1*cosf(angRad)), DEG2RAD(0.0f + 1*sinf(angRad)), DEG2RAD(0.0f));
        cam.angles.x = DEG2RAD(90.0f + 3*cosf(angRad));
        cam.angles.y = DEG2RAD(0.0f + 3*sinf(angRad));
        ang+=10;
        if(ang>=360)
            ang = 0;

        for(int j=0; j<cam.resolution.y; j++)
        {
            for(int i=0; i<cam.resolution.x; i++)
            {
                pixelRay = cam.getRayAtPixel(i, j);
                minDepth = 25000.0f;
                for(int p=0; p<5; p++)
                {
                    intersection = pixelRay.intersectWithPlane(*planeSet[p]);
                    curDepth = glm::length(intersection-cam.position);
                    if(curDepth<minDepth)
                        minDepth = curDepth;
                }
                
                rawPixelVal = minDepth/5;
                if(rawPixelVal>0xff)
                    rawPixelVal = 0xff;

                rawPixelVal = 255 - rawPixelVal;

                image[j*cam.resolution.x*3 + i*3] = (uint8_t)rawPixelVal;
                image[j*cam.resolution.x*3 + i*3 + 1] = (uint8_t)rawPixelVal;
                image[j*cam.resolution.x*3 + i*3 + 2] = (uint8_t)rawPixelVal;

                //image[i*cam.resolution.y*3 + j*3] = 255*(i*cam.resolution.y*3 + j*3)/(cam.resolution.x*cam.resolution.y*3); 
                //image[i*cam.resolution.y*3 + j*3 + 1] = 255*(i*cam.resolution.y*3 + j*3)/(cam.resolution.x*cam.resolution.y*3);
                //image[i*cam.resolution.y*3 + j*3 + 2] = 255*(i*cam.resolution.y*3 + j*3)/(cam.resolution.x*cam.resolution.y*3);
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