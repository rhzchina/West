#include "WelcomeScene.h"
#include "tool.h"
#include "StartScene.h"


WelcomeScene::WelcomeScene(void)
{
}


WelcomeScene::~WelcomeScene(void)
{
}

bool WelcomeScene::init(){
	bool success = false;
	do{
		CCLayer::init()	;
		setTouchEnabled(true);

		CCSprite* bg = CCSprite::create("shopBg.jpg");
		bg->setAnchorPoint(ccp(0,0));
		addChild(bg);

		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shop.plist","shop.png");

		CCMenu* menu = CCMenu::create();
		CC_BREAK_IF(!menu);
		SETANCHPOS(menu,480,240,0.5,0.5);
		addChild(menu);

		CCMenuItemSprite* close = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("close.png"),
			CCSprite::createWithSpriteFrameName("close.png"),this,menu_selector(WelcomeScene::btnCallback));
		SETANCHPOS(close,240,160,0,0);
		close->setTag(1);
		menu->addChild(close);

		CCMenuItemSprite* buy = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("buy.png"),
			CCSprite::createWithSpriteFrameName("buy.png"),this,menu_selector(WelcomeScene::btnCallback));
		SETANCHPOS(buy,240,-220,0,0);
		buy->setTag(2);
		menu->addChild(buy);
		//int x = 0;
		//int y = 300;
		//CCSprite* temp = NULL;
		//for (int i = 0;i <= 6; i++)
		//{
		//	char buf[30];
		//	sprintf(buf,"hero_%d.png",i);
		//	temp = CCSprite::create(buf);
		//	temp->setAnchorPoint(ccp(0,0));
		//	temp->setPosition(ccp(x,y));
		//	x += temp->getContentSize().width + 20;
		//	if(i < 3){
		//		y -= 80;
		//	}else{
		//		y += 80;
		//	}
		//	addChild(temp);
		//}
		success = true;
	}while(0);
	
	return success;
}

CCScene* WelcomeScene::scene(){
	CCScene* scene = NULL;

	do{
		 scene = CCScene::create();
		 CC_BREAK_IF(!scene);

		 WelcomeScene* layer = WelcomeScene::create();
		 CC_BREAK_IF(!layer);

		 scene->addChild(layer);
			
	}while(0);


	return scene;
}

void WelcomeScene::btnCallback(CCObject* sender){
	switch(((CCNode*)sender)->getTag()){
	case 1:
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
		CCDirector::sharedDirector()->replaceScene(StartScene::scene());
		break;
	case 2:
		CCLog("buy items");
		break;
	}
}