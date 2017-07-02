#ifndef __INGAME_DOT_H__
#define __INGAME_DOT_H__

#include "cocos2d.h"

USING_NS_CC;

class Dot {
public:
	// construstor
	Dot(cocos2d::Sprite* dotSpr, bool isFake);
	Dot(std::string filename, bool isFake);

	// pararms
	cocos2d::Sprite dotSprite;
	bool isFake;
	std::string filename;

	// methods
	bool IsCorrect(void);
	void SetPos(Vec2);
	void SetPos(float x, float y);
	Sprite* GetSprite();

	// pos & spr 
	Sprite* spr;
	Vec2 pos;
	float posX;
	float posY;
};

#endif
