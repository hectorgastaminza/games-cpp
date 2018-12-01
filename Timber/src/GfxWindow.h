/*
 * GfxWindows.h
 *
 *  Created on: Nov. 29, 2018
 *      Author: hecto
 */

#ifndef SRC_GFXWINDOW_H_
#define SRC_GFXWINDOW_H_

#include <SFML/Graphics.hpp>
#include <list>
#include <iterator>
#include <memory>
#include "GfxSprite.h"

class GfxWindow {
public:
	GfxWindow();
	GfxWindow(const std::string& title, unsigned int modeWidth, unsigned int modeHeight, unsigned int modeBitsPerPixel = 32);
	virtual ~GfxWindow();
	void addSprite(GfxSprite& sprite);
	void addSprite(sf::Drawable* drawable);
	void drawSprites(void);
	bool isOpen() const;
	bool pollEvent(sf::Event& event);
	void close();
	void clear();
	void display();
	void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
private:
	sf::RenderWindow _window;
	sf::VideoMode _videoMode;
	sf::View _view;
	std::list<sf::Drawable *> _drawables;
};

#endif /* SRC_GFXWINDOW_H_ */
