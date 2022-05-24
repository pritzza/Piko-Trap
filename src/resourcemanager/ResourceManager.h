#pragma once

#include "TextureResource.h"
#include "TextureID.h"

#include "../util/EnumArray.h"

template<typename ResourceType>
struct ManagedResource final
{
	ResourceType data;
	std::string dataPath;
	int usage{ 0 };

	// TODO ask someone knowledgable to help me understand why code doesnt run if
	// this default ctor doesn't exist
	ManagedResource() = default;

	ManagedResource(const std::string& dataPath)
		:
		dataPath{ dataPath }
	{}

};

class ResourceManager final
{
private:

	EnumArray<TextureID, ManagedResource<TextureResource>> resources
	{
		std::initializer_list < std::pair<TextureID, ManagedResource<TextureResource> >>
		{
			{ TextureID::Test1, ManagedResource<TextureResource>{"res/untitled.png"} },
			{ TextureID::Test2, ManagedResource<TextureResource>{"res/chara_01.png"} },
			{ TextureID::Test3, ManagedResource<TextureResource>{"res/pikmin wallpaper.jpg"} }
		}
	};

private:
	// loads or increments ManagedResource's usage
	void load(const TextureID textureID);

public:
	// returns data of resource type
	sf::Texture& get(const TextureID textureID);

	// unloads or decrements ManagedResource's usage
	// this MUST be called once for every get() call in code (RAII)
	void unload(const TextureID textureID);

};