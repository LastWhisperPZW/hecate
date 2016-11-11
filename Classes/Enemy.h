#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"
#include "Airplane.h"
#include "Bullet.h"

class GameSceneBackgroundLayer;

class Enemy{

	friend class GameSceneBackgroundLayer;

public:
	
	Enemy() :gameLayer(nullptr), enemyImgPath({ "enemy1.png", "enemy2.png" }), bulletImgPath({"bullet3.png" , "bullet4.png"}){
		lastGenTime.QuadPart = 0;
	}
	void init(cocos2d::Layer *);
	void generateEnemy();
	void generateBullet();
	void doMove();
	void doMoveBullet();
	void clearUp();

private:

	cocos2d::Layer *gameLayer;

	std::vector<std::string> enemyImgPath;
	std::list<Airplane *> enemyVec;
	std::vector<std::string> bulletImgPath;
	std::list<Bullet *> bulletVec;
	
	LARGE_INTEGER freq;
	LARGE_INTEGER lastGenTime;
	const int MARGIN = {30};

};


#endif