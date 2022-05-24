#include "ResourceManager.h"

void ResourceManager::load(const TextureID textureID)
{
	auto& resource = this->resources.getVal(textureID);

	if (resource.usage == 0)
		resource.data.load(resource.dataPath);
	else
		resource.usage++;
}

sf::Texture& ResourceManager::get(const TextureID textureID)
{
	auto& resource = this->resources.getVal(textureID);

	if (resource.usage == 0)
		this->load(textureID);
	
	return resource.data.get();
}

void ResourceManager::unload(const TextureID textureID)
{
	auto& resource = this->resources.getVal(textureID);

	// make sure we dont somehow end up with more "delete"s than "alloc"s
	//assert(resource.usage > 0);

	if (resource.usage > 0)
		resource.usage--;
	else
		resource.data.unload();

}