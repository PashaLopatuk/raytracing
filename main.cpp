#include <iostream>

#include "src/config/config.h"
#include "src/models/scene.hpp"
#include "src/window/window.hpp"
#include "src/vec/vec3.h"



using namespace std;


int main() {

    const Camera camera(
        vec3(-5, 0, 0),
        vec3(0)
    );

    const WindowSettings config = {600, 600};

    const Scene scene(camera, config);

    sf::RenderWindow* window = createWindow(config);

    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

    
    while (window->isOpen()) {
        sf::Event event;
        image.create(config.width, config.height, sf::Color::Black);

        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        
        
        
        texture.loadFromImage(image);
        sprite.setTexture(texture);

        window->clear();
        window->draw(sprite);
        window->display();
        
        }
    }

    return 0;
}
