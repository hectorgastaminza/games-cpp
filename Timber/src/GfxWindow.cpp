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
		unsigned int modeWidth, unsigned int modeHeight, unsigned int modeBitsPerPixel/* = 32*/)
{
	// Create a video mode object
	_videoMode = sf::VideoMode::getFullscreenModes()[0];
	if(_videoMode.isValid() == false)
	{
		_videoMode = sf::VideoMode(modeWidth, modeHeight, modeBitsPerPixel);
	}
	// Create and open a window for the game
	_window.create(_videoMode, title);
	// Low res code
	_view = sf::View(sf::FloatRect(0, 0, modeWidth, modeHeight));
	_window.setView(_view);
}

GfxWindow::~GfxWindow() {
}

void GfxWindow::addSprite(sf::Drawable * drawable)
{
	_drawables.push_back(drawable);
}

void GfxWindow::drawSprites(void)
{
	if(isOpen())
	{
		for (auto it : _drawables)
		{
			_window.draw(*it);
		}
	}
}

bool GfxWindow::isOpen() const
{
	return _window.isOpen();
}

bool GfxWindow::pollEvent(sf::Event& event)
{
	return _window.pollEvent(event);
}

void GfxWindow::close()
{
	return _window.close();
}

void GfxWindow::clear()
{
	return _window.clear();
}

void GfxWindow::display()
{
	return _window.display();
}

void GfxWindow::draw(const sf::Drawable& drawable, const sf::RenderStates& states /*= sf::RenderStates::Default*/)
{
	_window.draw(drawable, states);
}

