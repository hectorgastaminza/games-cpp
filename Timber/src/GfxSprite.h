/*
 * SmflSprite.h
 *
 *  Created on: Nov. 28, 2018
 *      Author: hecto
 */

#ifndef SRC_GFXSPRITE_H_
#define SRC_GFXSPRITE_H_

#include <SFML/Graphics.hpp>
#include <memory>

class GfxSprite : public sf::Drawable {
public:
	GfxSprite();
	GfxSprite(const std::string& imgFile);
	GfxSprite(std::shared_ptr<sf::Texture> texture);
	virtual ~GfxSprite();
	void setPosition(float x, float y);
	void setOrigin(float x, float y);
	void setRotation(float angle);
	const std::shared_ptr<sf::Texture> getTexture();
	const sf::Vector2f& getPosition() const;
	void hide(bool isHide);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite _sprite;
	// Create a texture to hold a graphic on the GPU
	std::shared_ptr<sf::Texture> _ptrTexture;
	bool _isHide = false;
};

#endif /* SRC_GFXSPRITE_H_ */
