/*
 * GfxSpriteSliding.cpp
 *
 *  Created on: Dec. 2, 2018
 *      Author: hecto
 */

#include "GfxSpriteSliding.h"
#include <random>

GfxSpriteSliding::GfxSpriteSliding()
{
}

GfxSpriteSliding::GfxSpriteSliding(const std::string& imgFile) : GfxSprite(imgFile)
{
}

GfxSpriteSliding::GfxSpriteSliding(std::shared_ptr<sf::Texture> texture) : GfxSprite(texture)
{
}

GfxSpriteSliding::~GfxSpriteSliding()
{
}

void GfxSpriteSliding::configureSlide(enum slidingDirection direction, float width, float heightmin, float heightmax, int maxtime)
{
	_direction = direction;
	_width = width;
	_heightMax = heightmax;
	_heightMin = heightmin;
	_maxtime = maxtime;
}

void GfxSpriteSliding::slide(float seconds)
{
	if(_active == false)
	{
		// Configuring sliding
		// How fast is
		_speed = (_width * _direction) / randomGenerator(4, _maxtime);

		// How high is
		float height =  randomGenerator(_heightMin, _heightMax);
		float pos_x = (_direction == slidingDirection::SLIDE_LEFT) ? _width : 0;
		setPosition(pos_x, height);
		hide(true);
		_active = true;
	}
	else
	{
		// Sliding sprite
		hide(false);
		setPosition((getPosition().x + (_speed * seconds)), getPosition().y);

		// Has the bee reached the right hand edge of the screen?
		if ((getPosition().x < 0) || (getPosition().x > _width))
		{
			// Set it up ready to be a whole new cloud next frame
			_active = false;
		}
	}
}

int GfxSpriteSliding::randomGenerator(int min, int max)
{
    static std::mt19937 rng;
    static bool init = true;

    if(init)
    {
    	rng.seed(std::random_device()());
    	init = false;
    }

    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

    return dist(rng);
}
