#include <vector>

#include <SFML/Graphics.hpp>

#include "shape.hpp"
#include "camera.hpp"
#include "pixel.hpp"
#include "light.hpp"
#include "../config/config.h"
#include "../vec/funcs.h"


struct Scene {
    std::vector<Shape> shapes;
    std::vector<Light> lights;

    Camera camera;
    WindowSettings config;

    Scene(
        Camera camera,
        WindowSettings config
    ) :
    shapes(),
    lights(),
    camera(camera),
    config(config)
    {}

    vec2 interpolateCoordinates(vec2 coords) {
        return coords / vec2(config.width, config.height) * 2.f - 1.f;
    }

    std::vector<std::vector<Pixel> > render() {
        std::vector<std::vector<Pixel> > result;

        for (auto const &shape: shapes) {
            std::vector<Pixel> shapePixels;

            for (int x = 0; x < config.width; x++) {
                for (int y = 0; y < config.height; y++) {
                    shapePixels.push_back(
                        renderShape(
                        vec2(x, y),
                        shape)
                    );
                }
            }

            result.push_back(shapePixels);
        }
    }

    Pixel renderShape(
        vec2 cameraPixel,
        Shape shape
    ) {
        const int x = cameraPixel.x;
        const int y = cameraPixel.y;

        vec2 currentPixel = interpolateCoordinates(cameraPixel) ;

        vec3 rayDirection= norm(camera.direction + vec3(1, currentPixel));

        vec2 intersection = vec2(0);

        switch(shape.type) {
            case Cube:
                intersection = calculateBoxIntersection(
                    camera,
                    rayDirection,
                    shape.position,
                    shape.size,
                    vec3(0)
                );
                break;

            case Sphere:
                intersection = calculateSphereIntersection(
                    camera,
                    rayDirection,
                    shape.position,
                    shape.size
                );
                break;
        }

        Pixel pixel = {x, y, sf::Color::Black};

        for (Light const &light: lights) {
            if (intersection.x > 0) {
                vec3 itPoint = camera.position + rayDirection * intersection.x;
                vec3 n = norm(itPoint);

                float diff = dot(n, light);
                int colorScalar = clamp(static_cast<int>(diff * 255), 10, 255);
                sf::Color color(colorScalar, colorScalar, colorScalar, 255);

                pixel.color = color;
            }
        }

        return pixel;
    }

    void updateCamera(Camera newCamera) {
        this->camera = newCamera;
    }

    void updateShapes(std::vector<Shape> newShapes) {
        this->shapes = newShapes;
    }

    void updateLight(std::vector<Light> newLights) {
        this->lights = newLights;
    }

    void addShape(Shape shape) {
        this->shapes.push_back(shape);
    }

    void addLight(Light light) {
        this->lights.push_back(light);
    }
};
