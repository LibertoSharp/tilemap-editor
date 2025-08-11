#ifndef ASSETLOADER_H
#define ASSETLOADER_H
#include "engine/Singleton.h"
#include <map>
#include <filesystem>
#include "SFML/System/Exception.hpp"
#include <iostream>

using namespace  std::filesystem;

template <typename Resource>
class AssetLoader {
protected:
    std::map<std::string, Resource*> resources;

public:
    explicit AssetLoader(path path);
    void LoadResources();

private:
    path localPath;
};

template<typename Resource>
AssetLoader<Resource>::AssetLoader(path path) : localPath(std::move(path)) {

}

template<typename Resource>
void AssetLoader<Resource>::LoadResources() {
    for (const auto& entry : recursive_directory_iterator(localPath)) {
        if (entry.is_regular_file()) {
            Resource* resource = nullptr;
            try{
                Resource* resource = new Resource(entry.path().string());
                path relativePath = relative(entry, localPath);
                relativePath = relativePath.parent_path() / relativePath.stem();
                resources.insert(std::make_pair( relativePath.string(),resource));
                std::cout << relativePath.string() << std::endl;
            } catch (sf::Exception& e) {
                if (resource) delete resource;
            }
        }
    }
}


#endif //ASSETLOADER_H
