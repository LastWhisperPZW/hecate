#ifndef _AIRPLANE_H_
#define _AIRPLANE_H_

#include "cocos2d.h"
#include <string>

class Airplane : public cocos2d::Sprite{
public:
	Airplane():crash(false),duringTime(0){
		shootTime.QuadPart = 0;
	}
	static Airplane *create(const std::string &);
	bool checkInnerBorder(const cocos2d::Vec2&);
	bool checkOuterBorder();
	LARGE_INTEGER getShootTime() const{ return shootTime; }
	void setShootTime(LARGE_INTEGER m){ shootTime = m; }
	bool getCrashState() const { return crash; }
	unsigned getCrashTime() const { return duringTime; }
	void setCrashState(){ crash = true; }
	void setCrashTime(unsigned dT){ duringTime = dT; }
	std::string getFileName() const { return fileName; }
private:
	LARGE_INTEGER shootTime;
	bool crash;
	unsigned duringTime;
	std::string fileName;
};



#endif