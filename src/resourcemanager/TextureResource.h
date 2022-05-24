#pragma once

#include "Resource.h"

#include <SFML/Graphics/Texture.hpp>
#include <cassert>

class TextureResource : public Resource
{
private:
	static constexpr bool SAFETY_CHECKS{ false };

private:
	sf::Texture* resource{ nullptr };

public:
	~TextureResource()	{ unload(); }

	void load(const std::string_view& filePath) override
	{
		if constexpr (SAFETY_CHECKS)
			assert(this->m_isLoaded == false && resource == nullptr);

		if (this->m_isLoaded == false && resource == nullptr)
		{
			resource = new sf::Texture();
			this->m_isLoaded = true;

			// if the file doesnt sucessfully load, unload the resource
			if (resource->loadFromFile(std::string{ filePath }) == false)
				unload();
		}
	}

	void unload() override
	{
		// this only exists because of the TODO on ResourceManager ctor's TODO
		if constexpr (SAFETY_CHECKS)
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