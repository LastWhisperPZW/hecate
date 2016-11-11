#include "GameResultSceneLayer.h"
#include "GameScene.h"
USING_NS_CC;

GameResultSceneLayer *GameResultSceneLayer::create(unsigned s){
	GameResultSceneLayer *grsl = new (std::nothrow) GameResultSceneLayer(s);
	if (grsl && grsl->init()){
		grsl->autorelease();
		return grsl;
	}
	CC_SAFE_DELETE(grsl);
	return nullptr;
}

bool GameResultSceneLayer::init(){

	if (!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	bg = Sprite::create("resultbg.png");
	bg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	addChild(bg);
	
	TTFConfig ttfConfig;
	ttfConfig.fontFilePath = "fonts/Marker Felt.ttf";
	ttfConfig.fontSize = 32;
	ttfConfig.distanceFieldEnabled = false;
	ttfConfig.outlineSize = 0;
	ttfConfig.glyphs = GlyphCollection::DYNAMIC;
	ttfConfig.customGlyphs = nullptr;

	resultLb = Label::createWithTTF(ttfConfig, "You Failed");
	resultLb->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 70.0f);
	addChild(resultLb);

	ttfConfig.fontSize = 24;
	std::ostringstream oss;
	oss << "score : " << score;
	scoreLb = Label::createWithTTF(ttfConfig, oss.str());
	scoreLb->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 30.0f);
	addChild(scoreLb);
	
	auto menuItemRetryLabel = Label::createWithTTF(ttfConfig, "Retry");
	auto menuItemRetry = MenuItemLabel::create(menuItemRetryLabel, [&](Ref *r)->void{retryGame(r); });
	
	auto menuItemQuitLabel = Label::createWithTTF(ttfConfig, "Quit");
	auto menuItemQuit = MenuItemLabel::create(menuItemQuitLabel, [&](Ref *r)->void{quitGame(r); });
	
	menu = Menu::create(menuItemRetry,menuItemQuit,nullptr);
	menu->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 20.0f);
	menuItemRetry->setPositionX(menuItemRetry->getPositionX() - 60.0f);
	menuItemQuit->setPositionX(menuItemQuit->getPositionX() + 60.0f);
	addChild(menu);

	return true;
}

void GameResultSceneLayer::quitGame(Ref *r){
	
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}

void GameResultSceneLayer::retryGame(cocos2d::Ref *r){
	auto scene = GameScene::create();
	clearUp();
	Director::getInstance()->replaceScene(scene);
}

void GameResultSceneLayer::clearUp(){

	removeChild(bg);
	removeChild(resultLb);
	removeChild(scoreLb);
	removeChild(menu);
	return;

}