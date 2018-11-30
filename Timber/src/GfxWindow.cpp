/*
 * GfxWindows.cpp
 *
 *  Created on: Nov. 29, 2018
 *      Author: hecto
 */

#include "GfxWindow.h"

GfxWindow::GfxWindow() {
}

GfxWindow::GfxWindow(const std::string& title,
		unsigned int modeWidth, unsigned int modeHeight, unsigned int modeBitsPerPixel = 32)
{
	// Create a video mode object
	_videoMode = sf::VideoMode::getFullscreenModes()[0];
	if(_videoMode.isValid() == false)
	{
		_videoMode = sf::VideoMode(modeWidth, modeHeight, modeBitsPerPixel);
	}
	// Create and open a window for the game
	_window = sf::RenderWindow(_videoMode, title, sf::Style::Default);
	// Low res code
	_view = sf::View(sf::FloatRect(0, 0, modeWidth, modeHeight));
	_window.setView(_view);
}

GfxWindow::~GfxWindow() {
}

