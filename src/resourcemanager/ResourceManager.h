#pragma once

#include "../util/EnumArray.h"
#include "TextureResource.h"
#include "TextureID.h"

template<typename ResourceType>
struct ManagedResource final
{

};

class ResourceManager final
{
private:

	/*
private:
	// loads or increments ManagedResource's usage
	void load(const TextureID textureID);

public:
	// returns data of resource type
	sf::Texture& get(const TextureID textureID);

	// unloads or decrements ManagedResource's usage
	// this MUST be called once for every get() call in code (RAII)
	void unload(const TextureID textureID);


	*/
};