#ifndef _WELCOME_SCENE_LAYER_H_
#define _WELCOME_SCENE_LAYER_H_

#include "cocos2d.h"

class WelcomeSceneLayer :public cocos2d::Layer{
public:
	virtual bool init() override;
	void clearUp();
	void playGame(cocos2d::Ref *);
	void quitGame(cocos2d::Ref *);
	CREATE_FUNC(WelcomeSceneLayer);
private:
	cocos2d::Sprite *bg;
	cocos2d::Label *nameLabel;
	cocos2d::Menu *menu;
	cocos2d::Label *copyright;
	cocos2d::Label *email;
};

#endif