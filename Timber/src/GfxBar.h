/*
 * GfxBar.h
 *
 *  Created on: Dec. 4, 2018
 *      Author: hecto
 */

#ifndef SRC_GFXBAR_H_
#define SRC_GFXBAR_H_

#include <SFML/Graphics.hpp>

class GfxBar : public sf::Drawable {
public:
	GfxBar(float value, float max, float width, float height);
	virtual ~GfxBar();
	void setForeColor(const sf::Color& color = sf::Color::White);
	void setBackColor(const sf::Color& color = sf::Color::Black);
	void setPosition(float x, float y);
	void setValue(float value);
	void addValue(float addValue);
	float& getValue();
	void hide(bool isHide);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void updateSprite();
	sf::RectangleShape _rectFore;
	sf::RectangleShape _rectBack;
	float _value;
	float _max;
	float _width;
	bool _isHide = false;
};

#endif /* SRC_GFXBAR_H_ */
