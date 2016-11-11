#ifndef _KEYBOARD_LISTENER_H_
#define _KEYBOARD_LISTENER_H_

#include "cocos2d.h"

class KeyboardListener{
public:
	KeyboardListener() :keyEvent(nullptr){
		std::memset(keyRecord, 0, sizeof(keyRecord));
	}
	void init();
	cocos2d::EventListenerKeyboard *getKeyEvent(){ return keyEvent; }
	const cocos2d::EventListenerKeyboard *getKeyEvent() const{ return keyEvent; }
private:
	cocos2d::EventListenerKeyboard *keyEvent;
public:
	static void setKeyRecord(cocos2d::EventKeyboard::KeyCode);
	static void unsetKeyRecord(cocos2d::EventKeyboard::KeyCode);
	static bool checkKeyRecord(cocos2d::EventKeyboard::KeyCode);
private:
	static unsigned long long keyRecord[4];
};


#endif