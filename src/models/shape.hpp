#include "../vec/vec3.h"

#ifndef SHAPE_HPP
#define SHAPE_HPP

enum ShapeType {
    Sphere,
    Cube
};

struct Shape {
    ShapeType type;
    vec3 position;
    int size;
};

#endif
