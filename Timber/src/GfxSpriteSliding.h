/*
 * GfxSpriteSliding.h
 *
 *  Created on: Dec. 2, 2018
 *      Author: hecto
 */

#ifndef SRC_GFXSPRITESLIDING_H_
#define SRC_GFXSPRITESLIDING_H_

#include "GfxSprite.h"
#include "EnumSlidingDirection.h"

class GfxSpriteSliding : public GfxSprite {
public:
	GfxSpriteSliding();
	GfxSpriteSliding(const std::string& imgFile);
	GfxSpriteSliding(std::shared_ptr<sf::Texture> texture);
	virtual ~GfxSpriteSliding();
	void configureSlide(enum slidingDirection direction, float width, float height, float minheight, int maxtime);
	void slide(float seconds);
private:
	int randomGenerator(int min, int max);
	float _speed = 0;
	bool _active = false;
	float _width = 0;
	float _heightMax = 0;
	float _heightMin = 0;
	int _maxtime = 120;
	enum slidingDirection _direction = slidingDirection::SLIDE_LEFT;
};

#endif /* SRC_GFXSPRITESLIDING_H_ */
