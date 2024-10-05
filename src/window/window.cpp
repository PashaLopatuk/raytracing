#include <SFML/Graphics.hpp>
#include "../config/config.h"
#include "SFML/Window/VideoMode.hpp"
#include <memory>

using namespace sf;

RenderWindow* createWindow(WindowSettings config) {
    VideoMode videoMode = VideoMode(config.width, config.height);
    return new RenderWindow(videoMode, "Window");
}
