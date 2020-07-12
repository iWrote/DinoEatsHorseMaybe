#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

class TextureHolder
{
private:
	
	// holds related pairs of String and Texture
	std::map<std::string, sf::Texture> m_Textures; //basically this can hold a vector of spritesheets 

	// A pointer to the singleton
	static TextureHolder* m_s_Instance;

public:
	TextureHolder();
	static sf::Texture* GetTexture(std::string const& filename);

};

#endif
