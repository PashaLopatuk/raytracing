#include "../vec/vec3.h"


struct Camera {
    vec3 position;
    vec3 direction;

    Camera(vec3 pos, vec3 dir): 
    position(pos), 
    direction(dir) 
    {
        
    }
};
