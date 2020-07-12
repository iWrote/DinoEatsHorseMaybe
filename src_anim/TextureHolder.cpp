#include "TextureHolder.h"
#include <assert.h>

using namespace sf;
using namespace std;

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(m_s_Instance == nullptr); //enforcing singleton, can only call this constructor once 
	m_s_Instance = this;
}

sf::Texture* TextureHolder::GetTexture(std::string const& filename)
{
	auto& m = m_s_Instance->m_Textures;
	// auto is map<string, Texture>

	auto keyValuePair = m.find(filename);
	


	// Did we find a match?
	if (keyValuePair != m.end())
	{
		
		return &(keyValuePair->second);
	}
	else
	{
		// File name not found, create texture
		auto& texture = m[filename];
		texture.loadFromFile(filename);

		return &texture;
	}
}