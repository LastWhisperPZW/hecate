#ifndef _GAME_RESULT_SCENE_LAYER_H_
#define _GAME_RESULT_SCENE_LAYER_H_

#include "cocos2d.h"

class GameResultSceneLayer :public cocos2d::Layer{

public:
	GameResultSceneLayer(unsigned s) :score(s){}
	virtual bool init() override;
	static GameResultSceneLayer *create(unsigned);
	void quitGame(cocos2d::Ref *);
	void retryGame(cocos2d::Ref *);
	void clearUp();
private:
	int score;
	cocos2d::Sprite *bg;
	cocos2d::Label *resultLb;
	cocos2d::Label *scoreLb;
	cocos2d::Menu *menu;

};




#endif