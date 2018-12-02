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
	_ptrTexture = std::make_shared<sf::Texture>();
	// Load a graphic into the texture
	_ptrTexture->loadFromFile(imgFile);
	// Attach the texture to the sprite
	_sprite.setTexture(*_ptrTexture);
}

GfxSprite::GfxSprite(std::shared_ptr<sf::Texture> texture)
{
	_ptrTexture = texture;
	// Attach the texture to the sprite
	_sprite.setTexture(*_ptrTexture);
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

const std::shared_ptr<sf::Texture> GfxSprite::getTexture()
{
	return _ptrTexture;
}

const sf::Vector2f& GfxSprite::getPosition() const
{
	return _sprite.getPosition();
}

void GfxSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(_isHide == false)
	{
		target.draw(_sprite, states);
	}
}

void GfxSprite::hide(bool isHide)
{
	_isHide = isHide;
}
