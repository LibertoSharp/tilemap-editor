#include "engine/Application.h"

void Application::run(unsigned width, unsigned height) {
    createManagers();
    createWindow(width,height);

    renderTarget.create(width,height,4);
    renderTarget.zoom(4);

    dtClock.start();
    while (window->isOpen()) {
        dt = dtClock.restart().asSeconds();
        while (const std::optional event = window->pollEvent())
        {
            performEvent(event);
            update();
        }

        window->clear();
        renderTarget.clear(Color::Black);
        render();
        renderTarget.display();
        window->draw(renderTarget);
        window->display();


    }
}

void Application::createWindow(unsigned width, unsigned heigth) {
    std::uint32_t window_style = sf::Style::Titlebar | sf::Style::Close;
    this->window = new RenderWindow(sf::VideoMode({width, heigth}), "Makean RPG", window_style);
    this->window->setFramerateLimit(144);
}

void Application::createManagers() {
    textureManager = new TextureManager( assetsPath / "textures", sf::Vector2i(16,16));
    textureManager->LoadResources();
}

void Application::render() {

}

void Application::update() {

}

void Application::performEvent(std::optional<Event> event) {
    if (event->is<sf::Event::Closed>())
    {
        window->close();
    }
}

