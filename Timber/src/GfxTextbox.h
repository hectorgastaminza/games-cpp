/*
 * GfxTextbox.h
 *
 *  Created on: Dec. 1, 2018
 *      Author: hecto
 */

#ifndef SRC_GFXTEXTBOX_H_
#define SRC_GFXTEXTBOX_H_

#include <SFML/Graphics.hpp>

class GfxTextbox : public sf::Drawable {
public:
	GfxTextbox();
	GfxTextbox(const sf::Vector2f& sizeTextbox, const std::string& fontFile, unsigned int fontSize = 30);
	virtual ~GfxTextbox();
	void setPosition(float x = 0, float y = 0);
	void setForeColor(const sf::Color& color = sf::Color::White);
	void setBackColor(const sf::Color& color = sf::Color::Black);
	void setText(const sf::String& string);
	void enableBackground(bool isEnable);
	void hide(bool isHide);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Text _text;
	sf::Font _font;
	sf::RectangleShape _rect;
	bool _isBackgroundEnable = true;
	bool _isHide = false;
};

#endif /* SRC_GFXTEXTBOX_H_ */
