#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
#include "Airplane.h"
#include "KeyboardListener.h"
#include "Bullet.h"

class GameSceneBackgroundLayer;

class Player{

	friend class GameSceneBackgroundLayer;

public:

	Player() :gameLayer(nullptr), playerImgPath({ "player1.png", "player2.png" }), playerCnt(1), playerDeadStatus({ false, false }), playerDeadDuring({0,0}), keyEvent(new KeyboardListener),
		bulletImgPath({"bullet1.png","bullet2.png"}){}
	void init(cocos2d::Layer *);

	Airplane *getPlayerByIdx(unsigned);
	const unsigned getPlayerCnt() const{ return playerCnt; }
	KeyboardListener *getKeyEventListener(){ return keyEvent.get(); }
	
	void doMove();
	void doShoot();
	void doMoveBullet();

	bool getPlayerDeadStatus(size_t i) const{ return playerDeadStatus.at(i); }
	void setPlayerDeadStatus(size_t i){ playerDeadStatus.at(i) = true; }
	unsigned getPlayerDeadDuring(size_t i) const { return playerDeadDuring.at(i); }
	void setPlayerDeadDuring(size_t i, unsigned dt){ playerDeadDuring.at(i) = dt; }

	void clearUp();

private:

	cocos2d::Layer *gameLayer;

	std::vector<std::string> playerImgPath;
	unsigned playerCnt;
	cocos2d::Vector<Airplane *> playerVec;
	std::vector<bool> playerDeadStatus;
	std::vector<unsigned> playerDeadDuring;
	std::shared_ptr<KeyboardListener> keyEvent;
	std::vector<std::string> bulletImgPath;
	std::list<Bullet *> bulletVec;

	LARGE_INTEGER freq;

public:

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode, cocos2d::Event *);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event *);

};

#endif