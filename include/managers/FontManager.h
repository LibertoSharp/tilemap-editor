#ifndef FONTMANAGER_H
#define FONTMANAGER_H
#include "SFML/Graphics/Texture.hpp"
#include "AssetLoader.h"
#include "SFML/Graphics/Font.hpp"

class FontManager : public AssetLoader<sf::Font>{
  public:
    explicit FontManager(const std::filesystem::path &path);

    const sf::Font* const getFont(std::string fileName) const;
};



#endif //FONTMANAGER_H