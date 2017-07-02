#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameHandler.h"

USING_NS_CC;


class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	// on start
	virtual bool init();

	// back to hello world scene
	void backToMenuScene();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	std::vector<cocos2d::Sprite*> dots;

	const char* CURRENTLEVEL = "m_current_level";
	const int DEFAULT_CURRENT_LEVEL = 0;
private:
	void InitGame();

	GameHandler gameHandler;

	std::vector<bool> ansList;
	bool isChose = false;

	bool onTouchBegan(Touch* tTouch, Event* eEvent);

	void OnChoseAns(bool isCorrect);
};

#endif // __GAME_SCENE_H__
