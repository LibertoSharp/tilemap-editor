#ifndef ASSETLOADER_H
#define ASSETLOADER_H
#include "engine/Singleton.h"
#include <map>
#include <filesystem>
#include <iostream>

template <typename Resource>
class AssetLoader {
protected:
    std::map<std::string, Resource*> resources;

public:
    explicit AssetLoader(std::filesystem::path path);
    void LoadResources();

private:
    std::filesystem::path localPath;
};

template<typename Resource>
AssetLoader<Resource>::AssetLoader(std::filesystem::path path) : localPath(std::move(path)) {

}

template<typename Resource>
void AssetLoader<Resource>::LoadResources() {
    for (const auto& entry : std::filesystem::directory_iterator(localPath)) {
        if (entry.is_regular_file()) {
            Resource* resource = new Resource();
            if (resource->loadFromFile(entry.path().string()))
                resources.insert(std::make_pair( entry.path().stem().string(),resource));
            else delete resource;
        }
    }
}


#endif //ASSETLOADER_H
