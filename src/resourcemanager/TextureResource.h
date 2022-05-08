#pragma once

#include "Resource.h"
#include "TextureID.h"

#include <SFML/Graphics/Texture.hpp>
#include <cassert>

class TextureResource : public Resource<TextureID>
{
private:
	sf::Texture* resource{ nullptr };

public:
	TextureResource() = default;
	TextureResource(const TextureID id)	{ load(id); }
	~TextureResource()					{ unload(); }

	void load(const TextureID id) override 
	{
		assert(this->m_isLoaded == false && resource == nullptr);

		if (this->m_isLoaded == false && resource == nullptr)
		{
			resource = new sf::Texture();
			this->m_isLoaded = true;

			static const std::string RESOURCES_PATH{ "res/" };
			const std::string filePath{ RESOURCES_PATH + "untitled.png" };

			// if the file doesnt sucessfully load, unload the resource
			if (resource->loadFromFile(filePath) == false)
				unload();
		}
	}

	void unload() override
	{
		assert(this->m_isLoaded && resource != nullptr);

		if (this->m_isLoaded)
		{
			delete resource;
			resource = nullptr;
		}
	}

	sf::Texture& get()
	{
		assert(resource != nullptr);

		if (resource != nullptr)
			return *resource;

		// if resource is anything but valid, we want the program to crash
	}
};