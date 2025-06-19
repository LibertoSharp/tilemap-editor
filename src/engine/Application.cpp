#include "engine/Application.h"

void Application::run(unsigned x, unsigned y) {
    textureManager = new TextureManager( assetsPath / "textures", sf::Vector2i(16,16));
    textureManager->LoadResources();


    std::uint32_t window_style = sf::Style::Titlebar | sf::Style::Close;
    auto window = sf::RenderWindow(sf::VideoMode({x, y}), "Makean RPG", window_style);
    window.setFramerateLimit(144);

    renderTarget.create(x,y,4);
    renderTarget.zoom(4);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            update();
        }

        window.clear();

        renderTarget.clear(sf::Color::Cyan);
        render();
        window.draw(renderTarget);
        window.display();
    }
}

void Application::render() {

}

void Application::update() {

}
