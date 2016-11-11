#ifndef _BOOM_H_
#define _BOOM_H_

#include "cocos2d.h"

class Boom : public cocos2d::Sprite{

public:
	Boom() :duringTime(0){}
	static Boom *create(const std::string &);
	unsigned getDuringTime() const{ return duringTime; }
	void setDuringTime(unsigned dT){ duringTime = dT; }
private:
	unsigned duringTime;

};


#endif