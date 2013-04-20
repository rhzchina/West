#include "WelcomeScene.h"
#include "tool.h"
#include "StartScene.h"


WelcomeScene::WelcomeScene(void)
{
	itemsLayer = NULL;
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


		createItems(CLOTHES);

		CCMenu* menu = CCMenu::create();
		CC_BREAK_IF(!menu);
		SETANCHPOS(menu,480,240,0.5,0.5);
		addChild(menu);

		CCMenuItemSprite* close = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("close.png"),
			CCSprite::createWithSpriteFrameName("close.png"),this,menu_selector(WelcomeScene::btnCallback));
		SETANCHPOS(close,260,170,0,0);
		close->setTag(-1);
		menu->addChild(close);

		CCMenuItemSprite* buy = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("buy.png"),
			CCSprite::createWithSpriteFrameName("buy.png"),this,menu_selector(WelcomeScene::btnCallback));
		SETANCHPOS(buy,240,-220,0,0);
		buy->setTag(0);
		menu->addChild(buy);

		CCMenuItemSprite* weapon = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("weapon.png"),
			CCSprite::createWithSpriteFrameName("weapon.png"),this,menu_selector(WelcomeScene::btnCallback));
		SETANCHPOS(weapon,-450,120,0,0);
		weapon->setTag(WEAPON);
		menu->addChild(weapon);

		CCMenuItemSprite* treasure = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("treasure.png"),
			CCSprite::createWithSpriteFrameName("treasure.png"),this,menu_selector(WelcomeScene::btnCallback));
		SETANCHPOS(treasure,-450,50,0,0);
		treasure->setTag(TREASURE);
		menu->addChild(treasure);

		CCMenuItemSprite* tip = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("tip.png"),
			CCSprite::createWithSpriteFrameName("tip.png"),this,menu_selector(WelcomeScene::btnCallback));
		SETANCHPOS(tip,-450,-20,0,0);
		tip->setTag(TIP);
		menu->addChild(tip);

		CCMenuItemSprite* clothes = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("clothes.png"),
			CCSprite::createWithSpriteFrameName("clothes.png"),this,menu_selector(WelcomeScene::btnCallback));
		SETANCHPOS(clothes,-450,-100,0,0);
		clothes->setTag(CLOTHES);
		menu->addChild(clothes);

		//用户数据信息显示
		CCSprite* gold = CCSprite::createWithSpriteFrameName("gold.png");
		SETANCHPOS(gold,122,420,0,0);
		addChild(gold);

		CCSprite* god = CCSprite::createWithSpriteFrameName("god.png");
		SETANCHPOS(god,350,420,0,0);
		addChild(god);

		CCSprite* star = CCSprite::createWithSpriteFrameName("star.png");
		SETANCHPOS(star,550,415,0,0);
		addChild(star);

		goldNum = CCLabelAtlas::create("5508","num/num_green.png",28,40,'0');
		SETANCHPOS(goldNum,550,415,0,0);
		addChild(goldNum);

		
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
	char str[50];
	switch(((CCNode*)sender)->getTag()){
	case -1:
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
		CCDirector::sharedDirector()->replaceScene(StartScene::scene());
		break;
	case 0:
		GameData::setGold(GameData::getGold() * 2);
		sprintf(str,"%d",GameData::getGold());
		goldNum->setString(str);
		CCLog("buy items");
		break;
	case WEAPON:
		createItems(WEAPON);
		break;
	case TREASURE:
		createItems(TREASURE);
		break;
	case TIP:
		createItems(TIP);
		break;
	case CLOTHES:
		createItems(CLOTHES);
		break;
	}
}

void WelcomeScene::createItems(int type){
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shop.plist","shop.png");

	if(scroll){
		removeChild(scroll,true);
	}
	itemsLayer = CCLayer::create();
	
	int x = 0;
	int count = 0;
	int max = 0;
	bool next = true;
	
	while(next){
		count++;
		CCSprite* bg = CCSprite::createWithSpriteFrameName("item_bg.png");
		CCSprite* item = NULL;
		char name[20];
		switch(type){
		case WEAPON:
			max = 7;
			sprintf(name,"weapon/weapon%d.png",count);
			item = CCSprite::create(name);
			break;
		case TREASURE:
			max = 1;
			break;
		case TIP:
			max = 3;
			sprintf(name,"tip/tip%d.png",count * 3);
			item = CCSprite::create(name);
			break;	
		case CLOTHES:
			max = 7;
			sprintf(name,"hero_%d.png",(count - 1));
			item = CCSprite::create(name);
			break;
		default:
			CCLog("type %d error",type);
			break;
		}
		SETANCHPOS(bg,x,0,0,0);
		itemsLayer->addChild(bg);
		if(item){
			itemsLayer->addChild(item);
			SETANCHPOS(item,x + bg->getContentSize().width / 2,120,0.5,0);
		}
		x += bg->getContentSize().width + 10;
		if(count >= max){
			next = false;
		}
	}
	itemsLayer->setContentSize(CCSizeMake(x,480 - 150));

	scroll = CCScrollView::create();
	SETANCHPOS(scroll,175,150,0,0);
	scroll->setDirection(kCCScrollViewDirectionHorizontal);
	scroll->setViewSize(CCSizeMake(max > 3 ? 854 - 150 : x,480 - 150));
	scroll->setContentSize(CCSizeMake(x,480 - 150));
	scroll->setContainer(itemsLayer);
	scroll->setContentOffset(CCPointZero);
	
	addChild(scroll);
}