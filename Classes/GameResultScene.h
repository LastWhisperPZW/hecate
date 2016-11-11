#ifndef _GAME_RESULT_SCENE_H_
#define _GAME_RESULT_SCENE_H_

#include "cocos2d.h"
#include "GameResultSceneLayer.h"

class GameResultScene :public cocos2d::Scene{
public:
	GameResultScene(unsigned s) :grsl(GameResultSceneLayer::create(s)){
		addChild(grsl);
	}
	static GameResultScene *create(unsigned);
private:
	GameResultSceneLayer *grsl;
};

#endif