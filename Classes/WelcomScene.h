#ifndef _WELCOME_SCENE_H_
#define _WELCOME_SCENE_H_

#include "cocos2d.h"
#include "WelcomeSceneLayer.h"

class WelcomeScene :public cocos2d::Scene{
public:
	WelcomeScene() :wsl(WelcomeSceneLayer::create()){ addChild(wsl); }
	CREATE_FUNC(WelcomeScene);
private:
	WelcomeSceneLayer *wsl;
};


#endif