#ifndef ASSETLOADER_H
#define ASSETLOADER_H
#include "engine/Singleton.h"
#include <map>
#include <filesystem>
#include <iostream>
#include <SFML/Graphics/Shader.hpp>
#include "SFML/System/Exception.hpp"
#include "../Common.h"

using namespace  std::filesystem;

template <typename Resource>
class AssetLoader {
protected:
    std::map<std::string, Resource*> resources;

public:
    explicit AssetLoader(path path);
    ~AssetLoader() {
        for (auto it = resources.begin(); it != resources.end(); it++) {
            delete it->second;
        }
    }

    const Resource* const getResource(const std::string& id);
    void loadResources();

private:
    path localPath;
};

template<typename Resource>
AssetLoader<Resource>::AssetLoader(path path) : localPath(std::move(path)) {

}

template<typename Resource>
const Resource* const AssetLoader<Resource>::getResource(const std::string& id) {
    return resources.find(id)->second;
};

template<typename Resource>
void AssetLoader<Resource>::loadResources() {
    for (const auto& entry : recursive_directory_iterator(localPath)) {
        if (entry.is_regular_file()) {
            Resource* resource = nullptr;
            try{
                resource = new Resource(entry.path().string());
                resources.insert(std::make_pair( RelativePath(entry,localPath).string(),resource));
            } catch (sf::Exception& e) {
                if (resource) delete resource;
            }
        }
    }
}

template<>
inline void AssetLoader<sf::Shader>::loadResources() {
    struct shader_files {
        string vertex;
        string fragment;
    };

    std::map<std::string, shader_files> shaders;
    for (const auto& entry : recursive_directory_iterator(localPath / "vertex")) {
        if (!entry.is_regular_file()) continue;
        if (shaders.empty() || shaders.find(entry.path().stem().string()) == shaders.end())
            shaders.insert(std::make_pair<string,shader_files>(entry.path().stem().string(), {entry.path().string(),"",}));
        else
            shaders[entry.path().stem().string()].vertex = entry.path().string();
    }
    for (const auto& entry : recursive_directory_iterator(localPath / "fragment")) {
        if (!entry.is_regular_file()) continue;
        if (shaders.empty() || shaders.find(entry.path().stem().string()) == shaders.end())
            shaders.insert(std::make_pair<string,shader_files>(entry.path().stem().string(), {"",entry.path().string()}));
        else
            shaders[entry.path().stem().string()].fragment = entry.path().string();
    }

    for (const auto& shader: shaders) {
        auto* shaderPtr = new sf::Shader();
        bool success = false;
        if (!shader.second.vertex.empty() && !shader.second.fragment.empty())
            success = shaderPtr->loadFromFile(shader.second.vertex, shader.second.fragment);
        else if (!shader.second.vertex.empty())
            success = shaderPtr->loadFromFile(shader.second.vertex, sf::Shader::Type::Vertex);
        else if (!shader.second.fragment.empty())
            success = shaderPtr->loadFromFile(shader.second.fragment, sf::Shader::Type::Fragment);

        if (success)
            resources.insert(make_pair(shader.first, shaderPtr));
    }
}
#endif //ASSETLOADER_H
