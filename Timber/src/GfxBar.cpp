/*
 * GfxBar.cpp
 *
 *  Created on: Dec. 4, 2018
 *      Author: hecto
 */

#include "GfxBar.h"

GfxBar::GfxBar(float value, float max, float width, float height)
{
	_value = value;
	_max = max;
	_width = width;
	_rectFore = sf::RectangleShape(sf::Vector2f(width, height));
	_rectBack = sf::RectangleShape(sf::Vector2f(width, height));
}
GfxBar::~GfxBar() {
	// TODO Auto-generated destructor stub
}
void GfxBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(_isHide == false)
	{
		if(_value > 0)
		{
			target.draw(_rectFore, states);
		}
		if(_value < _max)
		{
			target.draw(_rectBack, states);
		}
	}
}
void GfxBar::hide(bool isHide)
{
	_isHide = isHide;
}
void GfxBar::setForeColor(const sf::Color& color)
{
	_rectFore.setFillColor(color);
}
void GfxBar::setBackColor(const sf::Color& color)
{
	_rectBack.setFillColor(color);
	_rectFore.setOutlineColor(color);
	_rectFore.setOutlineThickness(2.0);
}
void GfxBar::setPosition(float x, float y)
{
	_rectFore.setPosition(x, y);
	updateSprite();
}
void GfxBar::addValue(float addValue)
{
	float aux = _value + addValue;
	if (aux < 0)
	{
		aux = 0;
	}
	else if (aux > _max)
	{
		aux = _max;
	}
	setValue(aux);
}
void GfxBar::setValue(float value)
{
	_value = value;
	updateSprite();
}
float& GfxBar::getValue()
{
	return _value;
}
void GfxBar::updateSprite()
{
	float aux = ((_width * _value) / _max);
	_rectFore.setSize(sf::Vector2f(aux, _rectFore.getSize().y));
	_rectBack.setSize(sf::Vector2f(_width - aux, _rectFore.getSize().y));
	_rectBack.setPosition(sf::Vector2f(_rectFore.getPosition().x + aux, _rectFore.getPosition().y));
}
