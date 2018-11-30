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
#include "GfxSprite.h"

class GfxWindow {
public:
	GfxWindow();
	GfxWindow(const std::string& title, unsigned int modeWidth, unsigned int modeHeight, unsigned int modeBitsPerPixel = 32);
	virtual ~GfxWindow();
private:
	sf::VideoMode _videoMode;
	sf::RenderWindow _window;
	sf::View _view;
	std::list<GfxSprite> _gfxSprites;
};

#endif /* SRC_GFXWINDOW_H_ */
