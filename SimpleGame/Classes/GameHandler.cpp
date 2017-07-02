#include "GameHandler.h"
#include "Dot.h"

GameHandler::GameHandler()
{
	CCLOG("GameHandler Constructor is called");
	this->curLevel = 0;
	this->colCount = 0;
	this->rowCount = 0;
	this->dotVec.clear();
}

void GameHandler::GenerateLevel(int level)
{
	CCLOG("GameHandler GenerateLevel is called");
	if (level <= 14) { // 2x2 dimension, total 4
		this->rowCount = 2;
		this->colCount = 2;
	}
	else if (level <= 28) { // 2x3 dimension, total 6
		this->rowCount = 2;
		this->colCount = 3;
	}
	else if (level <= 42) { // 2x4 dimension, total 8
		this->rowCount = 2;
		this->colCount = 4;
	}
	else if (level <= 56) { // 3x4 dimension, total 12
		this->rowCount = 3;
		this->colCount = 4;
	}
	else if (level <= 70) { // 4x4 dimension, total 16
		this->rowCount = 4;
		this->colCount = 4;
	}
	else if (level <= 84) { // 5x4 dimension, total 20
		this->rowCount = 5;
		this->colCount = 4;
	}
	else { // 6x4 dimension, total 24
		this->rowCount = 6;
		this->colCount = 4;
	}

	// test?
	this->rowCount = 6;
	this->colCount = 4;

	this->GenerateSprVec();
}

std::vector<Dot*> GameHandler::GetLevelVec()
{
	CCLOG("GameHandler GetLevelVec is called");
	return dotVec;
}

void GameHandler::GenerateSprVec()
{
	CCLOG("GameHandler GenerateSprVec is called");
	// reset vector
	this->dotVec.clear();

	// generate the question by random number
	int ansTmp = RandomHelper::random_int(0, 2);
	int fakeTmp = RandomHelper::random_int(0, 2);

	if (fakeTmp == ansTmp) {
		if (ansTmp == 0) {
			fakeTmp++;
		}
		else {
			fakeTmp--;
		}
	}

	std::string ansFilename = "";
	std::string fakeFilename = "";
	/*
	0: blue
	1: red
	2: green
	*/
	switch (ansTmp) {
	case 0:
		ansFilename = std::string("blue_dot.png");
		break;
	case 1:
		ansFilename = std::string("red_dot.png");
		break;
	case 2:
		ansFilename = std::string("green_dot.png");
		break;
	}
	switch (fakeTmp) {
	case 0:
		fakeFilename = std::string("blue_dot.png");
		break;
	case 1:
		fakeFilename = std::string("red_dot.png");
		break;
	case 2:
		fakeFilename = std::string("green_dot.png");
		break;
	}

	// generate the ans index within the array
	int randTargetIndex = RandomHelper::random_int(1, rowCount * colCount);
	log("Random Target Index: %d", randTargetIndex);
	// push new spr into vector
	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < colCount; j++) {
			
			CCLOG("Target: %d ; Cur: %d", randTargetIndex, i * rowCount + j);
			if (randTargetIndex != i * rowCount + j) { // generate fake items
				this->dotVec.push_back(new Dot(fakeFilename, false));
			}
			else { // generate ans item
				this->dotVec.push_back(new Dot(ansFilename, true));
				log("Generated Ans Item!!!");
			}
		}
	}
}

int GameHandler::GetRowCount() {
	CCLOG("GameHandler GetRowCount is called");
	return this->rowCount;
}

int GameHandler::GetColumnCount() {
	CCLOG("GameHandler GetColumnCount is called");
	return this->colCount;
}