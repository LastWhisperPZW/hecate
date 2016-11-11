#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "GameSceneBackgroundLayer.h"
#include <iostream>

class GameScene :public cocos2d::Scene{
public:
	GameScene() :gsbgl(GameSceneBackgroundLayer::create()){ 
		addChild(gsbgl);  		
	}
	CREATE_FUNC(GameScene);
private:
	GameSceneBackgroundLayer *gsbgl;
};

#endif