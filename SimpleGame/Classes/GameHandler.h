#ifndef __GAME_HANDLER_H__
#define __GAME_HANDLER_H__

#include "cocos2d.h"
#include "Dot.h"

USING_NS_CC;

class GameHandler {
public:

	GameHandler();

	int curLevel;
	std::vector<Dot*> dotVec;

	// level usage
	void GenerateLevel(int level);
	std::vector<Dot*> GetLevelVec();

	// getter
	int GetRowCount();
	int GetColumnCount();
private:
	// generate list of sprite
	void GenerateSprVec();

	// used to saving generated dot for rendering

	// level mapping
	int rowCount;
	int colCount;
};
#endif