#include "GameScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameHandler.h"

USING_NS_CC;

Scene* GameScene::createScene() {
	return GameScene::create();
}

bool GameScene::init() {
	// get visible size
	auto visibleSize = Director::getInstance()->getWinSize();

	// create menu, it's an autorelease object
	auto backItem = MenuItemImage::create("back_btn.png", "back_btn.png", CC_CALLBACK_0(GameScene::backToMenuScene, this));
	backItem->setPosition(Vec2(0 + backItem->getContentSize().width / 2, visibleSize.height - backItem->getContentSize().height / 2));
	
	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	InitGame();

	return true;
}

void GameScene::backToMenuScene() {
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameScene::InitGame()
{
	CCLOG("==== Starting to init game ====");
	// get screen size
	auto visibleSize = Director::getInstance()->getWinSize();

	// clear ans list
	ansList.clear();

	// get current level from user default
	auto userDefault = cocos2d::UserDefault::getInstance();
	int curLevel = userDefault->getIntegerForKey(CURRENTLEVEL, DEFAULT_CURRENT_LEVEL);
	gameHandler.GenerateLevel(curLevel);

	// setup basic UI
	std::string str = "Current Level: ";
	str += std::to_string(curLevel);
	auto label = Label::createWithTTF(str, "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - label->getContentSize().height));
	this->addChild(label);

	// get dot vector
	std::vector<Dot*> dotList = gameHandler.dotVec;

	// get dimension
	int row = gameHandler.GetRowCount();
	int column = gameHandler.GetColumnCount();

	for (int x = 0; x < row; x++) {
		for (int y = 0; y < column; y++) {
			Dot* dot = dotList.at(column*x + y);
			Sprite* sprClone = Sprite::create(dot->filename);
			ansList.push_back(dot->isFake);
			sprClone->setPosition(Vec2(sprClone->getContentSize().width + y * sprClone->getContentSize().width, sprClone->getContentSize().height + x * sprClone->getContentSize().height));
			sprClone->setTag(column*y+x);

			// setup onclick callback
			auto listener = EventListenerTouchOneByOne::create();
			listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprClone);

			this->addChild(sprClone);

			dots.push_back(sprClone);
		}
	}
}

bool GameScene::onTouchBegan(Touch * tTouch, Event * eEvent)
{
	for (int i = 0; i < dots.size(); i++) {
		if (dots.at(i)->getBoundingBox().containsPoint(tTouch->getLocation())) {
			if (ansList.at(i)) {
				// correct ans
				OnChoseAns(true);
				return true;
			}
			else {
				// wrong ans
				OnChoseAns(false);
				return true;
			}
		}
	}
	return false;
}

void GameScene::OnChoseAns(bool isCorrect)
{
	if (!isChose) {
		isChose = true;
		if (isCorrect) {
			auto userDefault = cocos2d::UserDefault::getInstance();
			int curLevel = userDefault->getIntegerForKey(CURRENTLEVEL, DEFAULT_CURRENT_LEVEL);
			curLevel++;
			userDefault->setIntegerForKey(CURRENTLEVEL, curLevel);

			auto scene = GameScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
		else {
			auto userDefault = cocos2d::UserDefault::getInstance();
			userDefault->setIntegerForKey(CURRENTLEVEL, 0);
			auto scene = HelloWorld::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	}
}
