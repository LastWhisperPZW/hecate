#include "GameSceneBackgroundLayer.h"
#include "AudioEngine.h"
#include "GameResultScene.h"
#include <iostream>

USING_NS_CC;


bool GameSceneBackgroundLayer::init(){

	if (!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize(); 
	Vec2 origin = Director::getInstance()->getVisibleOrigin(); 

	experimental::AudioEngine::lazyInit();
	experimental::AudioEngine::preload("shoot.mp3");
	experimental::AudioEngine::preload("blast.mp3");
	experimental::AudioEngine::preload("fail.mp3");
	experimental::AudioEngine::preload("backMusic.mp3");
	experimental::AudioEngine::play2d("backMusic.mp3", true, 0.4f);
	
	for (size_t idx = 0; idx < bgDownImgPath.size(); ++idx){
		auto bgs = Sprite::create(bgDownImgPath.at(idx));
		bgDown.pushBack(bgs);
		if (idx == 0){
			bgs->setPosition(visibleSize.width / 2 + origin.x, origin.y + bgs->getContentSize().height / 2);
		}
		else{
			bgs->setPosition(visibleSize.width / 2 + origin.x, origin.y + bgDownHeight + bgs->getContentSize().height / 2);
		}
		bgDownHeight += bgs->getContentSize().height;
		addChild(bgs);
	}

	for (size_t idx = 0; idx < bgUpImgPath.size(); ++idx){
		auto bgs = Sprite::create(bgUpImgPath.at(idx));
		bgUp.pushBack(bgs);
		if (idx == 0){
			bgs->setPosition(visibleSize.width / 2 + origin.x, origin.y + bgs->getContentSize().height / 2);
		}
		else{
			bgs->setPosition(visibleSize.width / 2 + origin.x, origin.y + bgUpHeight + bgs->getContentSize().height / 2);
		}
		bgUpHeight += bgs->getContentSize().height;
		addChild(bgs);
	}

	TTFConfig ttfConfig;
	ttfConfig.fontFilePath = "fonts/Marker Felt.ttf";
	ttfConfig.fontSize = 12;
	ttfConfig.distanceFieldEnabled = false;
	ttfConfig.outlineSize = 0;
	ttfConfig.glyphs = GlyphCollection::DYNAMIC;
	ttfConfig.customGlyphs = nullptr;

	scoreL = Label::createWithTTF(ttfConfig, "score");
	addChild(scoreL);
	scoreL->setPosition(Vec2(origin.x + visibleSize.width - 40.0f, origin.y + visibleSize.height - 15.0f));
	
	player.init(this);
	if (player.getPlayerCnt() == 1){
		if (player.getPlayerByIdx(0)){
			addChild(player.getPlayerByIdx(0));
		}
		std::ostringstream oss;
		oss << "player1:" << score.at(0);
		auto l_ = Label::createWithTTF(ttfConfig, oss.str());
		scoreLabel.pushBack(l_);
		scoreLabel.at(0)->setPosition(Vec2(origin.x + visibleSize.width - 40.0f, origin.y + visibleSize.height - 25.0f));
		addChild(scoreLabel.at(0));
	}
	enemy.init(this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(player.getKeyEventListener()->getKeyEvent(), this);
	this->scheduleUpdate();

	return true;

}

void GameSceneBackgroundLayer::clearUp(){

	experimental::AudioEngine::stopAll();
	experimental::AudioEngine::uncacheAll();
	player.clearUp();
	enemy.clearUp();
	for (auto iter = boom.begin(); iter != boom.end(); ++iter){
		removeChild(*iter);
	}
	for (auto &item : bgDown){
		removeChild(item);
	}
	for (auto &item : bgUp){
		removeChild(item);
	}
	removeChild(scoreL);
	if (player.getPlayerCnt() == 1){
		removeChild(scoreLabel.at(0));
	}
	return;

}

void GameSceneBackgroundLayer::update(float dt){
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	for (auto &item : bgDown){
		item->setPositionY(item->getPositionY() - 0.2f);
		if (item->getPositionY() + item->getContentSize().height / 2 <= origin.y){
			item->setPositionY(origin.y + bgDownHeight - item->getContentSize().height / 2);
		}
	}
	for (auto &item : bgUp){
		item->setPositionY(item->getPositionY() - 0.2f);
		if (item->getPositionY() + item->getContentSize().height / 2 <= origin.y){
			item->setPositionY(origin.y + bgUpHeight - item->getContentSize().height / 2);
		}
	}
	

	if (!player.getPlayerDeadStatus(0)){
	
		std::ostringstream oss;
		oss << "player1:" << score.at(0);
		scoreLabel.at(0)->setString(oss.str());
		player.doMove();
		player.doShoot();
		player.doMoveBullet();
		enemy.generateEnemy();
		enemy.generateBullet();
		enemy.doMove();
		enemy.doMoveBullet();
		updateBoom();
		judgeCrash(enemy.enemyVec, player.playerVec);
		fightPlayer(enemy.bulletVec, player.playerVec);
		fightEnemy(player.bulletVec, enemy.enemyVec);

	}
	else{

		unsigned left = player.getPlayerDeadDuring(0);
		if (left > 0){
			player.setPlayerDeadDuring(0, left - 1);
		}
		else{
			clearUp();
			auto resultScene = GameResultScene::create(score.at(0));
			Director::getInstance()->replaceScene(resultScene);
		}

	}

}

void GameSceneBackgroundLayer::onExit(){
	this->unscheduleUpdate();
	Layer::onExit();
}

bool GameSceneBackgroundLayer::judgeCross(Sprite *lhs, Sprite *rhs){

	if (lhs->getBoundingBox().intersectsRect(rhs->getBoundingBox())){

		/* from left-bottom */
		const Vec2 lb1 = { lhs->getPositionX() - lhs->getContentSize().width / 2, lhs->getPositionY() - lhs->getContentSize().height / 2 };
		const Vec2 rt1 = { lhs->getPositionX() + lhs->getContentSize().width / 2, lhs->getPositionY() + lhs->getContentSize().height / 2 };
		const Vec2 lb2 = { rhs->getPositionX() - rhs->getContentSize().width / 2, rhs->getPositionY() - rhs->getContentSize().height / 2 };
		const Vec2 rt2 = { rhs->getPositionX() + rhs->getContentSize().width / 2, rhs->getPositionY() + rhs->getContentSize().height / 2 };
	
		const Vec2 LB = { std::max<float>(lb1.x, lb2.x), std::max<float>(lb1.y, lb2.y) };
		const Vec2 RT = { std::min<float>(rt1.x, rt2.x), std::min<float>(rt1.y, rt2.y) };

		
		Image p1, p2;
		
		if (typeid(*lhs) == typeid(Airplane)){
			p1.initWithImageFile(dynamic_cast<Airplane *>(lhs)->getFileName());
		}
		else if (typeid(*lhs) == typeid(Bullet)){
			p1.initWithImageFile(dynamic_cast<Bullet *>(lhs)->getFileName());
		}

		if (typeid(*rhs) == typeid(Airplane)){
			p2.initWithImageFile(dynamic_cast<Airplane *>(rhs)->getFileName());
		}
		else if (typeid(*rhs) == typeid(Bullet)){
			p2.initWithImageFile(dynamic_cast<Bullet *>(rhs)->getFileName());
		}

		const Vec2 lt1 = { LB.x - (lhs->getPositionX() - lhs->getContentSize().width / 2), lhs->getPositionY() + lhs->getContentSize().height / 2 - RT.y };
		const Vec2 rb1 = { RT.x - (lhs->getPositionX() - lhs->getContentSize().width / 2), lhs->getPositionY() + lhs->getContentSize().height / 2 - LB.y };
		const Vec2 lt2 = { LB.x - (rhs->getPositionX() - rhs->getContentSize().width / 2), rhs->getPositionY() + rhs->getContentSize().height / 2 - RT.y };
		const Vec2 rb2 = { RT.x - (rhs->getPositionX() - rhs->getContentSize().width / 2), rhs->getPositionY() + rhs->getContentSize().height / 2 - LB.y };
		
		unsigned char *_d1 = p1.getData();
		unsigned char *_d2 = p2.getData();
		
		unsigned cnt = 0;
		
		for (int i1 = static_cast<int>(lt1.x), i2 = static_cast<int>(lt2.x); i1 <= static_cast<int>(rb1.x) && i2 <= static_cast<int>(rb2.x); ++i1, ++i2){
			for (int j1 = static_cast<int>(lt1.y), j2 = static_cast<int>(lt2.y); j1 <= static_cast<int>(rb1.y) && j2 <= static_cast<int>(rb2.y); ++j1, ++j2){
				int cap1 = *(_d1 + j1 * static_cast<int>(lhs->getContentSize().width) * 4 + i1 * 4 + 3);
				int cap2 = *(_d2 + j2 * static_cast<int>(rhs->getContentSize().width) * 4 + i2 * 4 + 3);
				if (cap1 >= 150 && cap2 >= 150)
					++cnt;
			}
		}

		if (cnt > static_cast<unsigned>((RT.y - LB.y) * (RT.x - LB.x)) / 8){
			return false;
		}
		
	}

	return true;

}

void GameSceneBackgroundLayer::fightEnemy(std::list<Bullet *> &bulletVec, std::list<Airplane *> &enemyVec){

	for (auto iterBullet = bulletVec.begin(); iterBullet != bulletVec.end();){
		bool flag = false; 
		for (auto iterEnemy = enemyVec.begin(); iterEnemy != enemyVec.end();){

			if (!judgeCross(*iterBullet, *iterEnemy)){	
				
				if (!(*iterEnemy)->getCrashState()){
					score.at(0) += 1;
					(*iterEnemy)->setCrashState();
					(*iterEnemy)->setCrashTime(30);
				}
				auto b = Boom::create("boom3.png");
				b->setPosition(Vec2(((*iterEnemy)->getPositionX() + (*iterBullet)->getPositionX()) / 2.0f, ((*iterEnemy)->getPositionY() + (*iterBullet)->getPositionY()) / 2.0f));
				b->setScale(0.1f);
				b->setDuringTime(30);
				boom.push_back(b);
				addChild(b);
				auto ac = ScaleBy::create(0.5f, 1.5f);
				b->runAction(ac);
				experimental::AudioEngine::play2d("blast.mp3", false, 0.2f);
				flag = true;
				break;

			}
			else{
				++iterEnemy;
			}
		}
		if (flag){
			auto iter = iterBullet;
			++iter;
			removeChild(*iterBullet);
			bulletVec.erase(iterBullet);
			iterBullet = iter;
		}
		else{
			++iterBullet;
		}
	}
	return;

}


void GameSceneBackgroundLayer::fightPlayer(std::list<Bullet *> &bulletVec, cocos2d::Vector<Airplane *> &playerVec){

	for (auto iterBullet = bulletVec.begin(); iterBullet != bulletVec.end();){
		if (!judgeCross(*iterBullet, playerVec.at(0))){
			auto b = Boom::create("boom3.png");
			b->setPosition(Vec2((playerVec.at(0)->getPositionX() + (*iterBullet)->getPositionX()) / 2.0f, (playerVec.at(0)->getPositionY() + (*iterBullet)->getPositionY()) / 2.0f));
			b->setScale(0.1f);
			addChild(b);
			auto ac = ScaleBy::create(0.5f, 1.5f);
			b->runAction(ac);
			experimental::AudioEngine::play2d("fail.mp3", false, 0.1f);
			if (!player.getPlayerDeadStatus(0)){
				player.setPlayerDeadStatus(0);
				player.setPlayerDeadDuring(0, 30);
			}
			auto iter = iterBullet;
			++iter;
			removeChild(*iterBullet);
			bulletVec.erase(iterBullet);
			iterBullet = iter;
			player.getKeyEventListener()->getKeyEvent()->onKeyPressed = nullptr;
			player.getKeyEventListener()->getKeyEvent()->onKeyReleased = nullptr;
			boom.push_back(b);
			continue;
		}
		++iterBullet;
	}
	return;

}

void GameSceneBackgroundLayer::judgeCrash(std::list<Airplane *> &enemyVec, cocos2d::Vector<Airplane *> &playerVec){

	for (auto iterEnemy = enemyVec.begin(); iterEnemy != enemyVec.end(); ++iterEnemy){
		if (!judgeCross(*iterEnemy, playerVec.at(0))){
			auto b = Boom::create("boom3.png");
			b->setPosition(Vec2((playerVec.at(0)->getPositionX() + (*iterEnemy)->getPositionX()) / 2.0f, (playerVec.at(0)->getPositionY() + (*iterEnemy)->getPositionY()) / 2.0f));
			b->setScale(0.1f);
			addChild(b);
			auto ac = ScaleBy::create(0.5f, 1.5f);
			b->runAction(ac);
			experimental::AudioEngine::play2d("fail.mp3", false, 0.1f);
			if (!player.getPlayerDeadStatus(0)){
				player.setPlayerDeadStatus(0);
				player.setPlayerDeadDuring(0, 30);
			}
			auto iter = iterEnemy;
			++iter;
			removeChild(*iterEnemy);
			enemyVec.erase(iterEnemy);
			iterEnemy = iter;
			player.getKeyEventListener()->getKeyEvent()->onKeyPressed = nullptr;
			player.getKeyEventListener()->getKeyEvent()->onKeyReleased = nullptr;
			boom.push_back(b);
			continue;
		}
	}

}

void GameSceneBackgroundLayer::updateBoom(){

	for (auto iter = boom.begin(); iter != boom.end();){
		unsigned ct = (*iter)->getDuringTime();
		if (ct == 0){
			auto it = iter;
			++it;
			removeChild((*iter));
			boom.erase(iter);
			iter = it;
		}
		else{
			(*iter)->setDuringTime(ct - 1);
			++iter;
		}
	}
	return;

}