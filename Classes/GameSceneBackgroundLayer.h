#ifndef _GAME_SCENE_BACKGROUND_LAYER_H_
#define _GAME_SCENE_BACKGROUND_LAYER_H_

#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include "Boom.h"


class GameSceneBackgroundLayer :public cocos2d::Layer{

public:

	GameSceneBackgroundLayer() : cocos2d::Layer(), bgDownImgPath({ "backDownImg1.jpg", "backDownImg2.jpg", "backDownImg3.jpg" }), 
		bgDownHeight(0.0), bgUpImgPath({ "backUpImg1.png", "backUpImg2.png" }), bgUpHeight(0.0), score({ 0, 0 }){}
	virtual bool init() override;
	virtual void onExit() override;
	void update(float);
	CREATE_FUNC(GameSceneBackgroundLayer);
	
	bool judgeCross(cocos2d::Sprite *, cocos2d::Sprite *);
	void fightEnemy(std::list<Bullet *> &,std::list<Airplane *> &);
	void fightPlayer(std::list<Bullet *> &, cocos2d::Vector<Airplane *> &);
	void judgeCrash(std::list<Airplane *> &, cocos2d::Vector<Airplane *> &);
	void updateBoom();

private:

	cocos2d::Vector<cocos2d::Sprite *> bgDown;
	const std::vector<std::string> bgDownImgPath;
	float bgDownHeight;
	cocos2d::Vector<cocos2d::Sprite *> bgUp;
	const std::vector<std::string> bgUpImgPath;
	float bgUpHeight;

	Player player;
	Enemy enemy;
	std::list<Boom *> boom;
	std::vector<unsigned> score;
	cocos2d::Label *scoreL;
	cocos2d::Vector<cocos2d::Label *> scoreLabel;

	void clearUp();

};

#endif