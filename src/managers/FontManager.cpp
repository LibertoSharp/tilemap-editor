#include "managers/FontManager.h"

FontManager::FontManager(const std::filesystem::path &path) : AssetLoader(path) {

}

const sf::Font* const FontManager::getFont(std::string fileName) const  {
    return resources.find(fileName)->second;
}
