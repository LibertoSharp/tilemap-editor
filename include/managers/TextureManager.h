#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "AssetLoader.h"
#include "SFML/Graphics/Sprite.hpp"

class TextureManager : public AssetLoader<sf::Texture>{
public:
    explicit TextureManager(const std::filesystem::path &path, sf::Vector2i tileSize);

    const sf::Texture* getAtlasTexture(const std::string& atlasName) const;
    sf::Sprite createTileSprite(const std::string& atlasName, int x, int y) const;
    sf::Sprite getSprite(const std::string& atlasName, sf::IntRect rect) const;
    sf::Sprite getSprite(const std::string& atlasName, int posx, int posy, int width, int height) const;

private:
    sf::Vector2i tileSize;
};





#endif //TEXTUREMANAGER_H
