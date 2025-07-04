#ifndef COMMON_H
#define COMMON_H
#include <cmath>
const float RadToDeg = 57.2958f;

inline sf::Vector2f Damp(const sf::Vector2f& source, const sf::Vector2f& target, float seconds, float dt) {
    float smoothing = std::pow(0.01f, 1.0f / seconds);
    float lerpFactor = 1.0f - std::pow(smoothing, dt);

    sf::Vector2f result;
    result.x = source.x + (target.x - source.x) * lerpFactor;
    result.y = source.y + (target.y - source.y) * lerpFactor;

    return result;
}
#endif //COMMON_H
