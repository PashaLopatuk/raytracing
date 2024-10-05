#include "src/vec/vec2.h"
#include "src/vec/vec3.h"
#include "src/vec/funcs.h"
#include <cstdio>
#include <iostream>


using namespace std;


int main() {
    int width = 143;
    int height = 40-2;
    float aspect = (float)width / height;
    float pixelAspect = 11.f / 24.0f;

    char gradient[] = " .:!/r(l1Z4H9W8$@";
    int gradientSize = sizeof(gradient) / sizeof(char);

    char* screen = new char[width * height + 1];
    screen[width * height] = '\0';
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                vec2 uv = vec2(i, j) / vec2(width, height) * 2.f -1.f;

                // uv.x = (float)i / width * 2.0f - 1.0f;
                // uv.y = (float)j / height * 2.0f - 1.0f;
                char pixel = ' ';

                vec3 ro = vec3(-5, 0, 0);
                vec3 rd = norm(vec3(1, uv));

                uv.x *= aspect * pixelAspect;

                vec2 intersection = sphere(ro, rd, 1);

                int color = 0;


                if (intersection.x > 0) {
                    color = 10;
                    pixel = '@';
                }

                color = clamp(color, 0, gradientSize);

                screen[i + j * width] = gradient[color];
            }
        }
        printf(screen);

    return 0;
}
