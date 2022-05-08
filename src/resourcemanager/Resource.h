#pragma once

template <typename ID>
class Resource
{
protected:
	bool m_isLoaded{ false };

public:
	
	// Recommendation:
	// Write RAII ctors and dtor 
	/*
	ResourceChild() = default;
	ResourceChild(ID id)	{ load(id); }
	~ResourceChild()		{ unload(); }
	*/

	virtual void load(const ID id) = 0;
	virtual void unload() = 0;
};