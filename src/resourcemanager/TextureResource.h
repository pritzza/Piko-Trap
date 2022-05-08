#pragma once

#include "Resource.h"
#include "TextureID.h"
#include <SFML/Graphics/Texture.hpp>
#include <cassert>

#include <iostream>

class TextureResource : public Resource<TextureID>
{
private:
	sf::Texture* resource{ nullptr };

public:
	TextureResource() = default;
	TextureResource(const TextureID id)
	{
		load(id);
	}
	~TextureResource() override
	{
		unload();
	}

	void load(const TextureID id) override 
	{
		assert(this->m_isLoaded == false && resource == nullptr);

		if (this->m_isLoaded == false && resource == nullptr)
		{
			resource = new sf::Texture();
			std::cout << "new\n";
			this->m_isLoaded = true;

			// if the file doesnt sucessfully load, unload the resource
			if (resource->loadFromFile("C:/Users/Jonat/Documents/Programming/VS C++/Piko Trap/res/untitled.png") == false)
				unload();
		}
	}

	void unload() override
	{
		assert(this->m_isLoaded && resource != nullptr);

		if (this->m_isLoaded)
		{
			delete resource;
			std::cout << "delete\n";
			resource = nullptr;
		}
	}

	sf::Texture& get()
	{
		//assert(resource != nullptr);

		if (resource != nullptr)
			return *resource;
	}
};