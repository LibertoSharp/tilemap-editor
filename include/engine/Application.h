#ifndef APPLICATION_H
#define APPLICATION_H
#include "Editor.h"
#include "graphics/PixelPerfectRenderTarget.h"
#include "GUI/GuiLayer.h"
#include "level/Level.h"
#include "managers/ShaderManager.h"
#include "managers/TextureManager.h"
#include "SFML/Graphics.hpp"

using namespace sf;

class Application : public Singleton<Application>{
public:
     Application() : Singleton<Application>(this) {}
    ~Application() {
         delete textureManager;
         delete window;
         delete fontManager;
         delete shaderManager;
         delete level;
         delete guiLayer;
         delete editor;
    }

    void run(unsigned width = 960, unsigned height = 540);

    TextureManager* getTextureManager() {
        return textureManager;
    }
    AssetLoader<Font>* getFontManager() {
        return fontManager;
    }
    ShaderManager *getShaderManager() {
        return shaderManager;
    }

    const float getDeltaTime() const {
        return dt;
    }

    const float getTime() const {
        return t;
    }

    Window* const getWindow() {
        return window;
    }

    Level* const getLevel() const {
        return level;
    }

private:
    void render();
    void update();
    void performEvent(std::optional<Event> event);
    void createWindow(unsigned width, unsigned height);
    void createManagers();

     bool CallGuiEvents();

    std::filesystem::path assetsPath = std::filesystem::current_path() / ".." / R"(assets)";
    TextureManager* textureManager = nullptr;
    AssetLoader<sf::Font>* fontManager = nullptr;
    ShaderManager *shaderManager = nullptr;

    Vector2i windowSize;
    RenderWindow* window{};
    gui::GuiLayer* guiLayer;
    PixelPerfectRenderTarget renderTarget;;
    Level *level;
    Editor *editor;

    Clock dtClock;
    float dt = 0; //seconds
    float t = 0; //seconds
};

#endif //APPLICATION_H
