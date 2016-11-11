#include "Player.h"
#include "AudioEngine.h"

USING_NS_CC;

void Player::init(Layer *layer){

	gameLayer = layer;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	if (playerCnt == 1){
		auto player1 = Airplane::create(playerImgPath.at(1));
		playerVec.pushBack(player1);
		player1->setScale(0.4f);
		player1->setPosition(visibleSize.width / 2 + origin.x, origin.y + player1->getBoundingBox().size.height / 2);
		QueryPerformanceFrequency(&freq);

	}

	keyEvent->init();
	keyEvent->getKeyEvent()->onKeyPressed = std::bind(&Player::onKeyPressed, this, std::placeholders::_1, std::placeholders::_2);
	keyEvent->getKeyEvent()->onKeyReleased = std::bind(&Player::onKeyReleased, this, std::placeholders::_1, std::placeholders::_2);
	
}


void Player::clearUp(){

	for (auto iter = bulletVec.begin(); iter != bulletVec.end(); ++iter){
		gameLayer->removeChild(*iter);
	}

	if (playerCnt == 1){
		gameLayer->removeChild(playerVec.at(0));
	}

	return;

}


void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event){
	KeyboardListener::setKeyRecord(keyCode);
	doMove();
	doShoot();
}

void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event){
	KeyboardListener::unsetKeyRecord(keyCode);
}

Airplane *Player::getPlayerByIdx(unsigned idx){
	if (idx >= playerCnt) return nullptr;
	return playerVec.at(idx);
}

void Player::doMove(){

	if (playerCnt == 1){
		Vector<FiniteTimeAction *> action;
		std::vector<Vec2> v = { { 0.0f, 3.0f }, { 0.0f, -3.0f }, { -3.0f, 0.0f }, { 3.0f, 0.0f } };
		std::vector<size_t> vb;
		if (KeyboardListener::checkKeyRecord(EventKeyboard::KeyCode::KEY_UP_ARROW) && 
			!KeyboardListener::checkKeyRecord(EventKeyboard::KeyCode::KEY_DOWN_ARROW)){
			vb.push_back(0);
		}
		if (KeyboardListener::checkKeyRecord(EventKeyboard::KeyCode::KEY_DOWN_ARROW) && 
			!KeyboardListener::checkKeyRecord(EventKeyboard::KeyCode::KEY_UP_ARROW)){
			vb.push_back(1);
		}
		if (KeyboardListener::checkKeyRecord(EventKeyboard::KeyCode::KEY_LEFT_ARROW) && 
			!KeyboardListener::checkKeyRecord(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)){
			vb.push_back(2);
		}
		if (KeyboardListener::checkKeyRecord(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) && 
			!KeyboardListener::checkKeyRecord(EventKeyboard::KeyCode::KEY_LEFT_ARROW)){
			vb.push_back(3);
		}
		if (vb.size()){
			Vec2 fin = { 0.0f, 0.0f };
			for (size_t i = 0; i < vb.size(); ++i){
				fin.x += v.at(vb.at(i)).x;
				fin.y += v.at(vb.at(i)).y;
			}
			float norm = std::sqrt(fin.x * fin.x + fin.y * fin.y);
			fin.x = fin.x / norm * 3.0f;
			fin.y = fin.y / norm * 3.0f;
			if (playerVec.at(0)->checkInnerBorder(fin)){
				auto ac = MoveBy::create(1.0f / 60.0f, fin);
				playerVec.at(0)->runAction(ac);
			}
		}
	}

}

void Player::doShoot(){

	if (playerCnt == 1){
		LARGE_INTEGER curTime;
		QueryPerformanceCounter(&curTime);
		if (KeyboardListener::checkKeyRecord(EventKeyboard::KeyCode::KEY_SPACE)
			&& (curTime.QuadPart < playerVec.at(0)->getShootTime().QuadPart || (static_cast<double>(curTime.QuadPart) - playerVec.at(0)->getShootTime().QuadPart) * 1000.0 /freq.QuadPart > 500.0)){
			playerVec.at(0)->setShootTime(curTime);
			auto bullet = Bullet::create(bulletImgPath.at(1));
			bullet->setPosition(Vec2(playerVec.at(0)->getPositionX(),playerVec.at(0)->getPositionY() + playerVec.at(0)->getBoundingBox().size.height / 2));
			bullet->setScale(0.6f);
			bullet->setOwner(0);
			bulletVec.push_back(bullet);
			gameLayer->addChild(bullet);
			experimental::AudioEngine::play2d("shoot.mp3", false, 0.5f);
		}
	}
}

void Player::doMoveBullet(){

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
