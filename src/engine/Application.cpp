#include "engine/Application.h"

#include "level/Level.h"

Level level;
void Application::run(unsigned width, unsigned height) {
    createManagers();
    createWindow(width,height);

    renderTarget.create(width,height,4);
    renderTarget.zoom(4);

    level.createGrid(16,100,100);

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
    std::uint32_t window_style = Style::Titlebar | Style::Close;
    this->window = new RenderWindow(VideoMode({width, heigth}), "Makean RPG", window_style);
    this->window->setFramerateLimit(144);
}

void Application::createManagers() {
    textureManager = new TextureManager( assetsPath / "textures", Vector2i(16,16));
    textureManager->LoadResources();
}

void Application::render() {
    renderTarget.draw(level);
}

void Application::update() {

}

void Application::performEvent(std::optional<Event> event) {
    if (event->is<sf::Event::Closed>())
    {
        window->close();
    }
    else if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed >()) {
        int viewZoom = renderTarget.getZoom() * level.getGrid()->getTileSize();
        level.getGrid()->setTile(mouseEvent->position.x / viewZoom,mouseEvent->position.y / viewZoom,Tile(textureManager->createTileSprite("plains",0,0)));
    }

}

