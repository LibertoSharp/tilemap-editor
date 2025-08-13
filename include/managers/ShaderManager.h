#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include "managers/AssetLoader.h"

class ShaderManager : public AssetLoader<shader_files> {
public:
	explicit ShaderManager(path localPath) : AssetLoader(localPath) {}

	inline sf::Shader* getShader(string id) {
		if (auto shader = resources.find(id); shader != resources.end()) {
			auto* shaderPtr = new sf::Shader();
			bool success = false;
			if (!shader->second->vertex.empty() && !shader->second->fragment.empty())
				success = shaderPtr->loadFromFile(shader->second->vertex, shader->second->fragment);
			else if (!shader->second->vertex.empty())
				success = shaderPtr->loadFromFile(shader->second->vertex, sf::Shader::Type::Vertex);
			else if (!shader->second->fragment.empty())
				success = shaderPtr->loadFromFile(shader->second->fragment, sf::Shader::Type::Fragment);

			if (success)
				return shaderPtr;
		}
		return nullptr;
	}
};
#endif //SHADERMANAGER_H
