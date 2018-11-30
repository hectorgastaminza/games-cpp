/*
 * SmflSprite.cpp
 *
 *  Created on: Nov. 28, 2018
 *      Author: hecto
 */

#include "GfxSprite.h"

GfxSprite::GfxSprite()
{
}

GfxSprite::GfxSprite(const std::string& imgFile)
{
	// Load a graphic into the texture
	_texture.loadFromFile(imgFile);
	// Attach the texture to the sprite
	_sprite.setTexture(_texture);
}

GfxSprite::GfxSprite(const sf::Texture & texture)
{
	_texture = texture;
	// Attach the texture to the sprite
	_sprite.setTexture(_texture);
}

GfxSprite::~GfxSprite() {
	// TODO Auto-generated destructor stub
}

void GfxSprite::setPosition(float x, float y)
{
	_sprite.setPosition(x,y);
}

void GfxSprite::setOrigin(float x, float y)
{

	_sprite.setOrigin(x,y);
}

void GfxSprite::setRotation(float angle)
{
	_sprite.setRotation(angle);
}

const sf::Texture & GfxSprite::getTexture()
{
	return _texture;
}

const sf::Vector2f& GfxSprite::getPosition() const
{
	return _sprite.getPosition();
}

sf::Sprite & GfxSprite::getSprite()
{
	return _sprite;
}

