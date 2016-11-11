#include "Airplane.h"

USING_NS_CC;

Airplane *Airplane::create(const std::string &t){
	Airplane *airplane = new (std::nothrow) Airplane();
	airplane->fileName = t;
	if (airplane && airplane->initWithFile(t)){
		airplane->autorelease();
		return airplane;
	}
	CC_SAFE_DELETE(airplane);
	return nullptr;
}

bool Airplane::checkInnerBorder(const Vec2 &m){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 p = getPosition();
	Rect r = getBoundingBox();

	float f = p.x - r.size.width / 2;
	if (m.x < -1e-8 && f - origin.x < -1.0 * m.x){
		return false;
	}
	f = p.x + r.size.width / 2;
	if (m.x > 1e-8 && origin.x + visibleSize.width - f < m.x){
		return false;
	}
	f = p.y - r.size.height / 2;
	if (m.y < -1e-8 && f - origin.y < -1.0 * m.y){
		return false;
	}
	f = p.y + r.size.height / 2 + m.y;
	if (m.y > 1e-8 && origin.y + visibleSize.height - f < m.y){
		return false;
	}

	return true;

}

bool Airplane::checkOuterBorder(){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 p = getPosition();
	Rect r = getBoundingBox();

	if (p.y + r.size.height / 2 < origin.y){
		return false;
	}

	return true;

}