#include "KeyboardListener.h"

USING_NS_CC;

unsigned long long KeyboardListener::keyRecord[4];

void KeyboardListener::setKeyRecord(cocos2d::EventKeyboard::KeyCode keyCode){
	keyRecord[(static_cast<unsigned>(keyCode) / 64)] |= (1ULL << (static_cast<unsigned>(keyCode) % 64));
}

void KeyboardListener::unsetKeyRecord(cocos2d::EventKeyboard::KeyCode keyCode){
	keyRecord[(static_cast<unsigned>(keyCode) / 64)] &= ~(1ULL << (static_cast<unsigned>(keyCode) % 64));
}

bool KeyboardListener::checkKeyRecord(cocos2d::EventKeyboard::KeyCode keyCode){
	return (keyRecord[(static_cast<unsigned>(keyCode) / 64)] & (1ULL << static_cast<unsigned>(keyCode) % 64)) > 0;
}

void KeyboardListener::init(){
	keyEvent = EventListenerKeyboard::create();
	keyEvent->setEnabled(true);
}
