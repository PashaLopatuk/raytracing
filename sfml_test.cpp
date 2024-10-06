#include <iostream>
#include <chrono>

#include <SFML/Graphics.hpp>
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "src/vec/funcs.h"
#include "src/vec/vec2.h"
#include "src/vec/vec3.h"
#include "src/window/window.hpp"


vec3 createMove(vec3 dir) {
    return norm( dir * 0.1 );
}

int main() {
    WindowSettings config = { 600, 600 };
    sf::RenderWindow* window = createWindow(config);

    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

    int t = 0;
    vec3 camera = vec3(-7, -2, 0);

    vec3 cameraDirection = norm(vec3(1, 0, 0));

    float moveSpeed = 0.1f;
    float lookSpeed = 0.1f;

    while (window->isOpen()) {
        sf::Event event;

        t++;

        image.create(config.width, config.height, sf::Color::Black);

        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) {
                    // camera = camera + createMove(cameraDirection);
                    camera.x += moveSpeed;
                }
                if (event.key.code == sf::Keyboard::A) {
                    camera.y -= moveSpeed;
                }
                if (event.key.code == sf::Keyboard::S) {
                    camera.x -= moveSpeed;
                }
                if (event.key.code == sf::Keyboard::D) {
                    camera.y += moveSpeed;
                }

                if (event.key.code == sf::Keyboard::Left) {
                    cameraDirection.y -= lookSpeed;
                }
                if (event.key.code == sf::Keyboard::Right) {
                    cameraDirection.y += lookSpeed;
                }
                if (event.key.code == sf::Keyboard::Up) {
                    cameraDirection.z -= lookSpeed;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    cameraDirection.z += lookSpeed;
                }

                }
            }


        vec3 light = norm(vec3(sin(t * 0.1), cos(t * 0.1), -1.0));

        vec3 sphere = vec3(0, 2, 0);
        vec3 box = vec3(0, 0, 0);

        for (int i = 0; i < config.width; i++) {
            for (int j = 0; j < config.height; j++) {
                vec2 currentPixel = vec2(i, j) / vec2(config.width, config.height) * 2.f - 1.f;

                vec3 rayDirection= norm(cameraDirection + vec3(1, currentPixel));

                vec2 intersectionWithSphere = calculateSphereIntersection(
                    camera,
                    rayDirection,
                    sphere,
                    1
                );

                vec3 cubeIntersectionNormal = vec3(0);

                vec2 intersectionWithCube = calculateBoxIntersection(
                    camera,
                    rayDirection,
                    box,
                    1,
                    cubeIntersectionNormal
                );

                if (intersectionWithSphere.x > 0) {
                    vec3 itPoint = camera + rayDirection * intersectionWithSphere.x;
                    vec3 n = norm(itPoint);

                    float diff = dot(n, light);
                    int colorScalar = clamp(static_cast<int>(diff * 255), 10, 255);
                    sf::Color color(colorScalar, colorScalar, colorScalar, 255);


                    image.setPixel(i, j, color);
                }

                if (intersectionWithCube.x > 0) {
                    vec3 itPointBox = camera + rayDirection * intersectionWithCube.x;
                    vec3 normalBox = norm(itPointBox);

                    float diffBox = dot(normalBox, light);
                    int colorScalarBox = clamp(static_cast<int>(diffBox * 255), 10, 255);
                    sf::Color colorBox(colorScalarBox, colorScalarBox, colorScalarBox, 255);

                    image.setPixel(i, j, colorBox);
                }
            }
        }

        if (t > 10000) {
            t = 0;
        }

        texture.loadFromImage(image);
        sprite.setTexture(texture);

        window->clear();
        window->draw(sprite);
        window->display();


    }

    delete window;
    return 0;
}
