#include "WelcomeSceneLayer.h"
#include "GameScene.h"

USING_NS_CC;

bool WelcomeSceneLayer::init(){

	if (!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	bg = Sprite::create("welcomebg.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	addChild(bg);

	TTFConfig ttfConfig;
	ttfConfig.fontFilePath = "fonts/Marker Felt.ttf";
	ttfConfig.fontSize = 32;
	ttfConfig.distanceFieldEnabled = false;
	ttfConfig.outlineSize = 0;
	ttfConfig.glyphs = GlyphCollection::DYNAMIC;
	ttfConfig.customGlyphs = nullptr;

	nameLabel = Label::createWithTTF(ttfConfig, "The Abbot's Airplane");
	nameLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 100.0f));
	addChild(nameLabel);

	ttfConfig.fontSize = 28;
	auto menuItemPlayLabel = Label::createWithTTF(ttfConfig, "Play");
	auto menuItemPlay = MenuItemLabel::create(menuItemPlayLabel,std::bind(&WelcomeSceneLayer::playGame,this,std::placeholders::_1));
	auto menuItemQuitLabel = Label::createWithTTF(ttfConfig, "Quit");
	auto menuItemQuit = MenuItemLabel::create(menuItemQuitLabel,std::bind(&WelcomeSceneLayer::quitGame,this,std::placeholders::_1));
	menu = Menu::create(menuItemPlay, menuItemQuit, nullptr);
	menuItemPlay->setPositionX(menuItemPlay->getPositionX() - 30.0f);
	menuItemQuit->setPositionX(menuItemQuit->getPositionX() + 30.0f);
	addChild(menu);

	ttfConfig.fontSize = 16;
	copyright = Label::createWithTTF(ttfConfig, "copyright 2016 by y5a9f2y");
	email = Label::createWithTTF(ttfConfig, "ydzhao1992@gmail.com");
	copyright->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 40.0f));
	email->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 20.0f));
	addChild(copyright);
	addChild(email);
	return true;

}

void WelcomeSceneLayer::clearUp(){
	
	removeChild(bg);
	removeChild(nameLabel);
	removeChild(menu);
	removeChild(copyright);
	removeChild(email);

}

void WelcomeSceneLayer::playGame(Ref *r){
	auto scene = GameScene::create();
	clearUp();
	Director::getInstance()->replaceScene(scene);
}

void WelcomeSceneLayer::quitGame(Ref *f){
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}