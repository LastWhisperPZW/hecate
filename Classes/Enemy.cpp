#include "Enemy.h"


USING_NS_CC;

void Enemy::init(Layer *layer){
	gameLayer = layer;
	QueryPerformanceFrequency(&freq);
}

void Enemy::clearUp(){

	for (auto iter = enemyVec.begin(); iter != enemyVec.end(); ++iter){
		gameLayer->removeChild(*iter);
	}
	for (auto iter = bulletVec.begin(); iter != bulletVec.end(); ++iter){
		gameLayer->removeChild(*iter);
	}
	return;

}

void Enemy::generateEnemy(){

	LARGE_INTEGER curTime;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	QueryPerformanceCounter(&curTime);
	if (curTime.QuadPart < lastGenTime.QuadPart || (static_cast<double>(curTime.QuadPart) - lastGenTime.QuadPart) * 1000.0f / freq.QuadPart > 2500.0f){
		int howMany = (std::rand() % 2) + 1;
		for (int i = 0; i < howMany; ++i){
			int h = (std::rand() % static_cast<int>(visibleSize.width));
			h = std::max<int>(MARGIN, h);
			h = std::min<int>(visibleSize.width - MARGIN, h);
			auto sp = Airplane::create(enemyImgPath.at(curTime.QuadPart % 2));
			sp->setScale(0.4f);
			sp->setPosition(Vec2(static_cast<float>(h)+origin.x, visibleSize.height + origin.y + sp->getBoundingBox().size.height / 2));
			bool flag = true;
			for (const auto &it : enemyVec){
				if (it->getBoundingBox().intersectsRect(sp->getBoundingBox())){
					flag = false;
					break;
				}
			}
			if (flag){
				gameLayer->addChild(sp);
				enemyVec.push_back(sp);
				lastGenTime = curTime;
			}
		}
		
	}

	return;

}


void Enemy::generateBullet(){

	LARGE_INTEGER curTime;
	QueryPerformanceCounter(&curTime);
	for (auto iter = enemyVec.begin(); iter != enemyVec.end(); ++iter){
		if ((*iter)->getCrashTime()) continue;
		if (curTime.QuadPart < (*iter)->getShootTime().QuadPart || (static_cast<float>(curTime.QuadPart) - static_cast<float>((*iter)->getShootTime().QuadPart)) * 1000.0f / freq.QuadPart > 3000.0f){
			int r = rand() % 2;
			if (r == 0) {
				continue;
			}
			(*iter)->setShootTime(curTime);
			auto b = Bullet::create(bulletImgPath.at(1));
			b->setScale(0.6f);
			b->setPosition(Vec2((*iter)->getPositionX(), (*iter)->getPositionY() - (*iter)->getBoundingBox().size.height / 2 - b->getBoundingBox().size.height));
			bulletVec.push_back(b);
			gameLayer->addChild(b);
		}
	}

}

void Enemy::doMove(){
	
	for (auto iter = enemyVec.begin(); iter != enemyVec.end();){
		if ((*iter)->getCrashState()){
			unsigned ct = (*iter)->getCrashTime();
			if (ct == 0){
				auto iterq = iter;
				++iterq;
				gameLayer->removeChild(*iter);
				enemyVec.erase(iter);
				iter = iterq;	
				continue;
			}
			else{
				(*iter)->setCrashTime(ct - 1);
			}
			
		}
		auto ac = MoveBy::create(1.0f / 60.0f, Vec2({ 0.0f, -0.5f }));
		(*iter)->runAction(ac);
		if (!(*iter)->checkOuterBorder()){
			auto iterq = iter;
			++iterq;
			gameLayer->removeChild(*iter);
			enemyVec.erase(iter);
			iter = iterq;
		}
		else{
			++iter;
		}
	}

}

void Enemy::doMoveBullet(){

	for (auto iter = bulletVec.begin(); iter != bulletVec.end();){
		(*iter)->moveBullet();
		if (!(*iter)->checkBorder()){
			auto iterq = iter;
			++iterq;
			gameLayer->removeChild(*iter);
			bulletVec.erase(iter);
			iter = iterq;
		}
		else{
			++iter;
		}
	}
	return;

}