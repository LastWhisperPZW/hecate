#ifndef _BULLET_H_
#define _BULLET_H_

#include "cocos2d.h"

class Bullet : public cocos2d::Sprite{
public:
	Bullet() :owner(-1){}
	static Bullet *create(const std::string &);
	int getOwner() const { return owner; }
	void setOwner(int o){ owner = o; }
	void moveBullet();
	bool checkBorder() const;
	std::string getFileName() const { return fileName; }
private:
	int owner;
	std::string fileName;
};

#endif