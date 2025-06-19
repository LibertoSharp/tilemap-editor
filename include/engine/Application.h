#ifndef APPLICATION_H
#define APPLICATION_H
#include "graphics/PixelPerfectRenderTarget.h"
#include "managers/TextureManager.h"
#include "SFML/Graphics.hpp"

class Application : Singleton<Application>{
public:
    explicit Application()
        : Singleton<Application>(this) {
    }

    void run(unsigned width = 960, unsigned height = 540);

    inline TextureManager* getTextureManager() {
        return textureManager;
    }

private:
    void render();
    void update();

    TextureManager* textureManager = nullptr;

    sf::Vector2i windowSize;
    std::filesystem::path assetsPath = std::filesystem::current_path() / ".." / R"(assets)";
    PixelPerfectRenderTarget renderTarget;
};

#endif //APPLICATION_H
