#pragma once

#include <string>
#include <string_view>

class Resource
{
protected:
	bool m_isLoaded{ false };

public:
	
	// Recommendation:
	// Write RAII ctors and dtor 
	/*
	ResourceChild() = default;
	ResourceChild(const std::string_view& filePath)	{ load(filePath); }
	~ResourceChild()								{ unload();		  }
	*/

	virtual void load(const std::string_view& filePath) = 0;
	virtual void unload() = 0;
};