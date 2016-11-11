#include "GameResultScene.h"

USING_NS_CC;

GameResultScene *GameResultScene::create(unsigned s){
	GameResultScene *grs = new (std::nothrow) GameResultScene(s);
	if (grs && grs->init()){
		grs->autorelease();
		return grs;
	}
	CC_SAFE_DELETE(grs);
	return nullptr;
}