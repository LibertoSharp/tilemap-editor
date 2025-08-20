#ifndef COMMON_H
#define COMMON_H
#include <cmath>
#include <fstream>
#include <SFML//System/Vector2.hpp>
#include "SFML/Graphics/Image.hpp"

using namespace  std::filesystem;
using namespace std;
const float RadToDeg = 57.2958f;

inline sf::Vector2f damp(const sf::Vector2f& source, const sf::Vector2f& target, float seconds, float dt) {
    float smoothing = std::pow(0.01f, 1.0f / seconds);
    float lerpFactor = 1.0f - std::pow(smoothing, dt);

    sf::Vector2f result;
    result.x = source.x + (target.x - source.x) * lerpFactor;
    result.y = source.y + (target.y - source.y) * lerpFactor;

    return result;
}

template<typename T>
inline string vec2tostring(const sf::Vector2<T>& source) {
    stringstream ss;
    ss << "X: " << source.x << " Y: " << source.y;
    return ss.str();
}

inline path RelativePath(path fullPath, path localPath) {
    path relativePath = relative(fullPath, localPath);
    relativePath = relativePath.parent_path() / relativePath.stem();
    return relativePath;
}

inline bool isEmptySprite(sf::Image& s, sf::IntRect r) {
    for (unsigned int x = r.position.x; x < r.size.x+r.position.x; x++) {
        for (unsigned int y = r.position.y; y < r.size.y+r.position.y; y++) {
            if (s.getPixel({x,y}).a != 0)
                return false;
        }
    }
    return true;
}

template <typename T>
void write_raw(std::ofstream& f, const T& value) {
    f.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

template <typename T>
void write_raw(std::ofstream& f, const T& value, int size) {
    f.write(reinterpret_cast<const char*>(&value), size);
}

#endif //COMMON_H
