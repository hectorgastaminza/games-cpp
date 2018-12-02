/*
 * GfxTextbox.cpp
 *
 *  Created on: Dec. 1, 2018
 *      Author: hecto
 */

#include "GfxTextbox.h"

GfxTextbox::GfxTextbox() {
	// TODO Auto-generated constructor stub

}

GfxTextbox::~GfxTextbox() {
	// TODO Auto-generated destructor stub
}

GfxTextbox::GfxTextbox(const sf::Vector2f& sizeTextbox, const std::string& fontFile, unsigned int fontSize)
{
	// Set font
	_font.loadFromFile(fontFile);
	// Set the font to our message
	_text.setFont(_font);
	// Set font size
	_text.setCharacterSize(fontSize);
	// Backgrounds for the text
	_rect.setSize(sizeTextbox);
}
void GfxTextbox::setPosition(float x, float y)
{
	_rect.setPosition(x, y);
}
void GfxTextbox::setForeColor(const sf::Color& color)
{
	_text.setFillColor(color);
}
void GfxTextbox::setBackColor(const sf::Color& color)
{
	_rect.setFillColor(color);
}
void GfxTextbox::setText(const sf::String& string)
{
	_text.setString(string);
	//Reposition the text based on its new size
	sf::FloatRect textRect = _text.getLocalBounds();
	_text.setOrigin(textRect.left + (textRect.width / 2.0f),
		textRect.top + (textRect.height / 2.0f));
	// Set new position in the background
	_text.setPosition((_rect.getPosition().x + (_rect.getSize().x / 2.0f)),
			(_rect.getPosition().y + (_rect.getSize().y / 2.0f)));
}
void GfxTextbox::enableBackground(bool isEnable)
{
	_isBackgroundEnable = isEnable;
}
void GfxTextbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(_isHide == false)
	{
		if(_isBackgroundEnable)
		{
			target.draw(_rect, states);
		}
		target.draw(_text, states);
	}
}
void GfxTextbox::hide(bool isHide)
{
	_isHide = isHide;
}
