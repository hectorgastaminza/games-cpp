/*
 * SmflSprite.cpp
 *
 *  Created on: Nov. 28, 2018
 *      Author: hecto
 */

#include "gfxSprite.h"

gfxSprite::gfxSprite()
{
}

gfxSprite::gfxSprite(const std::string& imgFile)
{
	// Load a graphic into the texture
	_texture.loadFromFile(imgFile);
	// Attach the texture to the sprite
	_sprite.setTexture(_texture);
}

gfxSprite::gfxSprite(const sf::Texture & texture)
{
	_texture = texture;
	// Attach the texture to the sprite
	_sprite.setTexture(_texture);
}

gfxSprite::~gfxSprite() {
	// TODO Auto-generated destructor stub
}

void gfxSprite::setPosition(float x, float y)
{
	_sprite.setPosition(x,y);
}

void gfxSprite::setOrigin(float x, float y)
{

	_sprite.setOrigin(x,y);
}

void gfxSprite::setRotation(float angle)
{
	_sprite.setRotation(angle);
}

const sf::Texture & gfxSprite::getTexture()
{
	return _texture;
}

const sf::Vector2f& gfxSprite::getPosition() const
{
	return _sprite.getPosition();
}

sf::Sprite & gfxSprite::getSprite()
{
	return _sprite;
}

