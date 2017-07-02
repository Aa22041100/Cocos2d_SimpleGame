#include "Dot.h"
#include "cocos2d.h"

USING_NS_CC;

Dot::Dot(Sprite* dotSpr, bool isFake) {
	this->isFake = isFake;
	this->spr = dotSpr;
}

Dot::Dot(std::string f, bool isFake)
{
	filename = f;
	this->isFake = isFake;
}

bool Dot::IsCorrect(void)
{
	return !isFake;
}

void Dot::SetPos(Vec2 targetPos)
{
	this->pos = targetPos;
}

void Dot::SetPos(float x, float y)
{
	posX = x;
	posY = y;
}

Sprite * Dot::GetSprite()
{
	return this->spr;
}
