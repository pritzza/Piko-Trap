#pragma once

template <typename ID>
class Resource
{
protected:
	bool m_isLoaded{ false };

public:
	Resource() = default;
	virtual Resource(const ID id) = 0;
	virtual ~Resource() = 0;

	virtual void load(const ID id) = 0;
	virtual void unload() = 0;
};