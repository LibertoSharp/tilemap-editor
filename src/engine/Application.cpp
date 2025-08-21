#include "engine/Application.h"
#include "../GUI/MainGUI.cpp"
#include "level/Level.h"

void Application::run(unsigned width, unsigned height) {
    createManagers();
    createWindow(width,height);

    renderTarget.create(width,height,1);
    renderTarget.zoom(4);

    editor = new Editor(&level);
    guiLayer = createEditorGui(editor);
    level = new Level(16 , 10, 10);

    dtClock.start();
    while (window->isOpen()) {
        dt = dtClock.restart().asSeconds();
        t += dt;
        ctx.Reset();
        while (const std::optional event = window->pollEvent())
        {
            performEvent(event);
        }
        update();
        window->clear(Color(26,26,30,255));
        renderTarget.clear(Color::Transparent);

        render();
        renderTarget.display();
        window->draw(*level->getBackgroundGrid());
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
    textureManager->loadResources();

    fontManager = new AssetLoader<Font>(assetsPath / "fonts");
    fontManager->loadResources();

    shaderManager = new ShaderManager(assetsPath / "shaders");
    shaderManager->loadResources();
}

void Application::render() {
    renderTarget.draw(*level);
}

bool Application::CallGuiEvents() {
    ctx.f_mouseDown = isButtonPressed(sf::Mouse::Button::Left);
    ctx.f_wheelDown = isButtonPressed(sf::Mouse::Button::Middle);
    if (!window->hasFocus()) ctx.Reset();
    Vector2i mousePos = sf::Mouse::getPosition(*window);
    Vector2u windowSize = window->getSize();

    ctx.mousePos = mousePos;
    ctx.is_inside_window = windowSize.x > mousePos.x && windowSize.y > mousePos.y;
    guiLayer->ctx = ctx;
    return guiLayer->callEvents();
}

void Application::update() {
    bool mouseOverGUI = CallGuiEvents();
    editor->update(ctx, mouseOverGUI);
}

void Application::performEvent(std::optional<Event> event) {
    if (event->is<sf::Event::Closed>())
        window->close();
    else if (const auto* mousePressedEvent = event->getIf<sf::Event::MouseButtonPressed >()) {
        if (mousePressedEvent->button == Mouse::Button::Left)
            ctx.f_clickDown = true;
        if (mousePressedEvent->button == Mouse::Button::Middle)
            ctx.f_wheelClick = true;
    } else if (const auto* mouseReleasedEvent = event->getIf<sf::Event::MouseButtonReleased >()) {
        if (mouseReleasedEvent->button == Mouse::Button::Left)
            ctx.f_clickUp = true;
        if (mouseReleasedEvent->button == Mouse::Button::Middle)
            ctx.f_wheelUp = true;
    } else if (const auto* mouseWheelEvent = event->getIf<sf::Event::MouseWheelScrolled>()) {
        ctx.mouse_wheel_delta = mouseWheelEvent->delta;
    } else if (const auto* textEnteredEvent = event->getIf<sf::Event::TextEntered>()) {
        ctx.textEntered = textEnteredEvent->unicode;
    }
    else if (const auto* keyPressedEvent = event->getIf<sf::Event::KeyPressed>()) {
        ctx.keyPressed = keyPressedEvent->code;
    }
}

