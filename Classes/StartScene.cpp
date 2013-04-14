#include "StartScene.h"
#include "GameScene.h"
#include "tool.h"
#include "GameData.h"

StartScene::StartScene(void)
{
}


StartScene::~StartScene(void)
{
}

bool StartScene::init(){
	bool success = false;
	do{
		CCSprite* bg = CCSprite::create("startBg.jpg");
		CC_BREAK_IF(!bg);

		SETANCHPOS(bg,0,0,0,0);
		addChild(bg);
		char* btnText = NULL;
		CONV(btnText,"开始游戏");
		CCMenuItemImage* startBtn = CCMenuItemImage::create("btn_bg.png","btn_bg.png",this,menu_selector(StartScene::btnCallback));
		CCMenuItemFont* startFont = CCMenuItemFont::create(btnText);
		startFont->setColor(ccc3(230,150,100));
		CCMenu* startMenu = CCMenu::create(startBtn,startFont,NULL);
	
		CONV(btnText,"商城");
		CCMenuItemImage* shopBtn = CCMenuItemImage::create("btn_bg.png","btn_bg.png",this,menu_selector(StartScene::btnCallback));
		CCMenuItemFont* shopFont = CCMenuItemFont::create(btnText);
		CCMenu* shopMenu = CCMenu::create(shopBtn,shopFont,NULL);

		CONV(btnText,"退出游戏");
		CCMenuItemImage* exitBtn = CCMenuItemImage::create("btn_bg.png","btn_bg.png",this,menu_selector(StartScene::btnCallback));
		CCMenuItemFont* exitFont = CCMenuItemFont::create(btnText);
		CCMenu* exitMenu = CCMenu::create(exitBtn,exitFont,NULL);

		SETANCHPOS(startMenu,750,200,0,0);
		SETANCHPOS(shopMenu,750,130,0,0);
		SETANCHPOS(exitMenu,750,50,0,0);
	
		startBtn->setTag(1);
		shopBtn->setTag(2);
		exitBtn->setTag(3);

		addChild(startMenu);
		addChild(shopMenu);
		addChild(exitMenu);


		success = true;
	}while(false);
	return success; 
}

CCScene* StartScene::scene(){
	CCScene* scene = NULL;
	
	do{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);

		StartScene* layer = StartScene::create();
		CC_BREAK_IF(!layer);

		scene->addChild(layer);
			
	}while(false);

	return scene;
}

void StartScene::btnCallback(CCObject* sender){
	switch(((CCNode*)sender)->getTag()){
	//startBtn
	case 1:
		CCDirector::sharedDirector()->replaceScene(SelectScene::scene());
		break;
	//shopBtn
	case 2:
		GameData::getInstance();
		GameData::addLevel();
		CCLog("%d",GameData::getLevel());
		break;
	case 3:
		CCDirector::sharedDirector()->end();
		break;
	}
}