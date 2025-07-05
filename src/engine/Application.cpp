#include "engine/Application.h"
#include "../GUI/MainGUI.cpp"
#include "level/Level.h"

void Application::run(unsigned width, unsigned height) {
    createManagers();
    createWindow(width,height);

    renderTarget.create(width,height,4);
    renderTarget.zoom(4);

    guiLayer = createMainMenu();

    dtClock.start();
    while (window->isOpen()) {
        dt = dtClock.restart().asSeconds();
        while (const std::optional event = window->pollEvent())
        {
            performEvent(event);
        }
        update();
        window->clear();
        renderTarget.clear(Color::Green);

        render();
        renderTarget.display();

        window->draw(renderTarget);
        window->draw(*guiLayer);
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

    fontManager = new FontManager(assetsPath / "fonts");
    fontManager->LoadResources();
}

void Application::render() {

}

void Application::CallGuiEvents() {
    guiLayer->ctx.f_mouseDown = isButtonPressed(sf::Mouse::Button::Left);
    if (!window->hasFocus()) guiLayer->ctx.Reset();
    guiLayer->ctx.mousePos = sf::Mouse::getPosition(*window);

    guiLayer->callEvents();
}

void Application::update() {
    CallGuiEvents();
}

void Application::performEvent(std::optional<Event> event) {
    if (event->is<sf::Event::Closed>())
        window->close();
    else if (const auto* mousePressedEvent = event->getIf<sf::Event::MouseButtonPressed >()) {
        if (mousePressedEvent->button == Mouse::Button::Left)
        guiLayer->ctx.f_clickDown = true;
    } else if (const auto* mouseReleasedEvent = event->getIf<sf::Event::MouseButtonReleased >()) {
        if (mouseReleasedEvent->button == Mouse::Button::Left)
        guiLayer->ctx.f_clickUp = true;
    }

}

