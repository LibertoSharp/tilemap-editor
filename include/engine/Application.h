#ifndef APPLICATION_H
#define APPLICATION_H
#include "graphics/PixelPerfectRenderTarget.h"
#include "GUI/GuiLayer.h"
#include "managers/TextureManager.h"
#include "SFML/Graphics.hpp"

using namespace sf;

class Application : public Singleton<Application>{
public:
     Application() : Singleton<Application>(this) {}
    ~Application() {
        delete textureManager;
        delete window;
    }

    void run(unsigned width = 960, unsigned height = 540);

    TextureManager* getTextureManager() {
        return textureManager;
    }

    const float getDeltaTime() const {
        return dt;
    }

private:
    void render();
    void update();
    void performEvent(std::optional<Event> event);
    void createWindow(unsigned width, unsigned height);
    void createManagers();
    void CallGuiEvents();

    std::filesystem::path assetsPath = std::filesystem::current_path() / ".." / R"(assets)";
    TextureManager* textureManager = nullptr;

    Vector2i windowSize;
    RenderWindow* window{};
    GuiLayer guiLayer;
    PixelPerfectRenderTarget renderTarget;

    Clock dtClock;
    float dt{}; //seconds
};

#endif //APPLICATION_H
