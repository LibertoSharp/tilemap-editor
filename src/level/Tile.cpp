#include <utility>

#include "level/Tile.h"

#include "engine/Application.h"

Tile::Tile(IntRect r, std::string atlasID): sprite(Application::getInstance()->getTextureManager()->getSprite(atlasID, r)) {
	this->atlasID = atlasID;
	this->rect = r;
}
