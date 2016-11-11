#include "Bullet.h"

USING_NS_CC;

Bullet *Bullet::create(const std::string &t){

	Bullet * bullet = new (std::nothrow) Bullet();
	bullet->fileName = t;
	if (bullet &&bullet->initWithFile(t)){
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;

}

void Bullet::moveBullet(){

	Vec2 m(0.0f, 3.0f);
	if (owner == -1){
		m.y *= -1.0f;
	}
	auto moveby = MoveBy::create(1.0f / 60.0f, m);
	runAction(moveby);

}

bool Bullet::checkBorder() const{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 position = getPosition();
	Size bounding = getBoundingBox().size;

	if (position.x + bounding.width / 2 < origin.x){
		return false;
	}
	if (position.x - bounding.width / 2 > origin.x + visibleSize.width){
		return false;
	}
	if (position.y + bounding.height / 2 < origin.y){
		return false;
	}
	if (position.y - bounding.width / 2 > origin.y + visibleSize.height){
		return false;
	}
	
	return true;

}