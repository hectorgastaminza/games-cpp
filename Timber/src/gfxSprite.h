/*
 * SmflSprite.h
 *
 *  Created on: Nov. 28, 2018
 *      Author: hecto
 */

#ifndef SRC_GFXSPRITE_H_
#define SRC_GFXSPRITE_H_

#include <SFML/Graphics.hpp>

class gfxSprite {
public:
	gfxSprite();
	gfxSprite(const std::string& imgFile);
	gfxSprite(const sf::Texture & texture);
	virtual ~gfxSprite();
	void setPosition(float x, float y);
	void setOrigin(float x, float y);
	void setRotation(float angle);
	const sf::Texture & getTexture();
	const sf::Vector2f& getPosition() const;
	sf::Sprite & getSprite();
private:
	// Create a texture to hold a graphic on the GPU
	sf::Texture _texture;
	sf::Sprite _sprite;
};

#endif /* SRC_GFXSPRITE_H_ */