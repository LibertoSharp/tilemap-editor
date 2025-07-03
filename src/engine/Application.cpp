#include "engine/Application.h"
#include "GUI/MainGUI.h"
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
            update();
        }

        window->clear();
        renderTarget.clear(Color::Green);

        render();
        renderTarget.display();

        window->draw(renderTarget);
        window->draw(guiLayer);
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

}

void Application::CallGuiEvents() {
    GuiEventContext ctx;
    ctx.mousePos = sf::Mouse::getPosition(*window);
    ctx.mouseDown = isButtonPressed(sf::Mouse::Button::Left);
    guiLayer.callEvents(ctx);
}

void Application::update() {
    CallGuiEvents();
}

void Application::performEvent(std::optional<Event> event) {
    if (event->is<sf::Event::Closed>())
    {
        window->close();
    }
    else if (const auto* mousePressedEvent = event->getIf<sf::Event::MouseButtonPressed >()) {
        GuiEventContext ctx;
        ctx.mousePos = mousePressedEvent->position;
        ctx.clickDown = true;
        guiLayer.callEvents(ctx);
    } else if (const auto* mouseReleasedEvent = event->getIf<sf::Event::MouseButtonReleased >()) {
        GuiEventContext ctx;
        ctx.mousePos = mouseReleasedEvent->position;
        ctx.clickUp = true;
        guiLayer.callEvents(ctx);
    }

}

