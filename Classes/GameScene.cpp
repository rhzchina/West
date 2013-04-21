#include "GameScene.h"
#include "StartScene.h"
#include "GameData.h"
#include <math.h>
GameScene::GameScene(void)
{
	scrollBg1 = NULL;
	scrollBg = NULL;
	bgX = 0;
	speed = 0.5;
	map = NULL;
	hero = NULL;
	overText = NULL;
	items = NULL;
	pauseLayer = NULL;
}


GameScene::~GameScene(void)
{

}

bool GameScene::init(){
	bool bRet = false;
	do{
		CC_BREAK_IF(!CCLayer::init());
		setTouchEnabled(true);

		initBgItems(GameData::getLevel());

		//scrollBg1 = CCSprite::createWithTexture(scrollBg->getTexture());

		overText = CCLabelTTF::create("Game OVer!!!\nTouch screen to replay,Let's go","黑体",30);
		overText->setColor(ccc3(255,0,0));
		overText->setPosition(ccp(425,240));
		overText->setVisible(false);

		//CC_BREAK_IF(!scrollBg1);

		addChild(overText,1);
		//addChild(scrollBg1);
		//scrollBg1->setAnchorPoint(ccp(0,0));

		//scrollBg1->setPosition(ccp(scrollBg->getContentSize().width,0));
		//初始化地图
		map = new Map(1,this);
		//生成主角
		hero = new Role(this);

		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("game.plist","game.png");

		CCSprite* scorePeach = CCSprite::createWithSpriteFrameName("score_peach.png");
		SETANCHPOS(scorePeach,600,420,0,0);
		addChild(scorePeach,10);


		CCSprite* distance = CCSprite::createWithSpriteFrameName("distance.png");
		SETANCHPOS(distance,0,430,0,0);
		addChild(distance,10);


		CCSprite* best = CCSprite::createWithSpriteFrameName("best.png");
		SETANCHPOS(best,20,390,0,0);
		addChild(best,10);

		scoreValue = CCLabelAtlas::create("0","num/num_green.png",28,40,'0');
		SETANCHPOS(scoreValue,680,420,0,0);
		addChild(scoreValue,10);

		distanceValue = CCLabelAtlas::create("0","num/num_yellow.png",28,40,'0');
		SETANCHPOS(distanceValue,170,430,0,0);
		addChild(distanceValue,10);

		char b[20];
		sprintf(b,"%d",GameData::getBest());
		bestValue = CCLabelAtlas::create(b,"num/num_red.png",28,40,'0');
		SETANCHPOS(bestValue,140,390,0,0);
		addChild(bestValue,10);

		progressBg = CCSprite::createWithSpriteFrameName("progress.png");
		SETANCHPOS(progressBg,200,0,0,0);
		addChild(progressBg,14);

		progressLeaf = CCSprite::createWithSpriteFrameName("thumb_leaf.png");
		SETANCHPOS(progressLeaf,200,0,0,0);
		addChild(progressLeaf,14);

		CCMenu* menu = CCMenu::create();
		SETANCHPOS(menu,20,0,0,0);
		addChild(menu,12);

		CCMenuItemSprite* pause = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("pause.png"),
			CCSprite::createWithSpriteFrameName("pause.png"),this,menu_selector(GameScene::btnCallback));
		SETANCHPOS(pause,0,0,0,0);
		pause->setTag(1);
		menu->addChild(pause);


		schedule(schedule_selector(GameScene::bgMove));
		bRet = true;
	}while(0);
	return bRet;
}

CCScene* GameScene::scene(){
	CCScene* scene = CCScene::create();
	GameScene* layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

void GameScene::ccTouchesBegan(CCSet* touches,CCEvent* event){
	if(!CCDirector::sharedDirector()->isPaused()){
		CCTouch* touch = (CCTouch*)touches->anyObject();
		CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
		hero->jump();
		if(hero->isDie()){
			GameData::reset(false);
			CCDirector::sharedDirector()->replaceScene(StartScene::scene());
		}
	}
}

void GameScene::ccTouchesMoved(CCSet* touches,CCEvent* event){

}

void GameScene::ccTouchesEnded(CCSet* touches,CCEvent* event){
	if(CCDirector::sharedDirector()->isPaused()){
		hero->hold();
	}
}

void GameScene::bgMove(float dt){
	GameData::addLoop();
	if(GameData::getLoop() % 5 == 0){
		GameData::addDistance(speed * 2);
		GameData::addScore(speed * 5);
	}
	char v[20];
	sprintf(v,"%d",GameData::getDistance());
	distanceValue->setString(v);
	sprintf(v,"%d",GameData::getScore());
	scoreValue->setString(v);

	map->mapMove(this,hero);
	if(hero->getSprite()->getPositionY() < 130){
		if(map->onLand(hero->getSprite())){
			if(hero->getState() != Role::FALL && hero->getState() != Role::ATTACK){
				hero->changeState(Role::NORMAL);
			}else if(hero->getState() == Role::ATTACK){
				hero->hold();
			}
		}else{
			if(hero->getState() != Role::ATTACK && hero->getState() != Role::HOLD)
				hero->fall();
		}
	}else if(hero->getSprite()->getPositionY() == 130){
		if(!map->onLand(hero->getSprite())) {
			hero->fall();
		}
	}

	if(map->weaponOn(hero)){
		hero->weaponDone(map->getSpeed(),dt);
	}

	if(hero->isDie()){
		unschedule(schedule_selector(GameScene::bgMove));
		overText->setVisible(true);
	}

	if(items->getPositionX() > -items->getContentSize().width){
		items->setPositionX(items->getPositionX() - speed / 2);
	}else{
		srand(time(0));
		if(rand() % 10 == 5){
			items->setPositionX(854);
		}
	}
}

void GameScene::initBgItems(int level){
	char dir[20];
	sprintf(dir,"land%d/",level);
	string name(dir);
	scrollBg = CCSprite::create(name.append("bg.jpg").c_str());
	SETANCHPOS(scrollBg,0,0,0,0);
	addChild(scrollBg,-2);

	char tempName[20];
	CCSprite* temp = NULL;
	items = CCLayer::create();
	int x = 0;
	switch(level){
	case 3:
		break;
	case 4:
		break;
	case 1:
		items->setContentSize(CCSizeMake(1380,480));
		//水晶宫
		name.replace(name.begin(),name.end(),dir);
		temp = CCSprite::create(name.append("sea_house.png").c_str());
		SETANCHPOS(temp,400,0,0.5,0);
		items->addChild(temp);
		//海中的山
		for(int i = 0; i < 3;i++){
			sprintf(tempName,"land%d/hill%d.png",level,(i+1));
			temp = CCSprite::create(tempName);
			SETANCHPOS(temp,x,0,0,0);
			items->addChild(temp,-1);
			x += temp->getContentSize().width;
		}
		//水晶宫前门牌
		temp = CCSprite::create(name.replace(name.begin(),name.end(),dir).append("plate.png").c_str());
		SETANCHPOS(temp,700,0,0,0);
		items->addChild(temp);
		//珊瑚和石头hk:海葵
		x =100;
		for(int i = 0;i < 5; i++){
			srand(time(0) + i);
			sprintf(tempName,"land%d/stone%d.png",level,(rand() % 5 + 1));
			temp = CCSprite::create(tempName);
			SETANCHPOS(temp,x,0,0,0);
			items->addChild(temp,3);
			int height = temp->getContentSize().height;
			srand(time(0) - i);
			sprintf(tempName,"land%d/plant%d.png",level,(rand() % 5 + 1));
			temp = CCSprite::create(tempName);
			SETANCHPOS(temp,x,height / 3,0,0);
			items->addChild(temp,2);
			int space = temp->getContentSize().width;

			if(rand() % 5 == i){
				sprintf(tempName,"land%d/hk.png",level);
				temp = CCSprite::create(tempName);
				SETANCHPOS(temp,x,0,0,0);
				items->addChild(temp,3);
			}
			srand(time(0) + (i + 1) * 2);
			x += space * (rand() % 3 + 2);
		}
		break;
	case 2:
		//石人碉像
		name.replace(name.begin(),name.end(),dir);
		temp = CCSprite::create(name.append("stone.png").c_str());
		SETANCHPOS(temp,854,0,1,0);
		items->addChild(temp);
		//背后的山	
		for(int i = 0; i < 2;i++){
			sprintf(tempName,"land%d/hill%d.png",level,(i+1));
			temp = CCSprite::create(tempName);
			SETANCHPOS(temp,x,0,0,0);
			items->addChild(temp,-1);
			x += temp->getContentSize().width;
		}
		//前方的草地
		x = 0;
		for(int i = 0; i < 8;i++){
			sprintf(tempName,"land%d/grass%d.png",level,rand() % 2 + 1);
			temp = CCSprite::create(tempName);
			SETANCHPOS(temp,x,rand() % 30,0,0);
			items->addChild(temp,1);
			x += temp->getContentSize().width * 3 / (rand() % 2 + 2);
		}
		break;
	}
	SETANCHPOS(items,0,0,0,0);
	addChild(items);
}

void GameScene::btnCallback(CCObject* sender){
	switch(((CCNode*)sender)->getTag()){
	case 1:
		CCDirector::sharedDirector()->pause();	
		showPauseLayer(true);
		break;
	case 2:
		showPauseLayer(false);
		CCDirector::sharedDirector()->resume();
		break;
	case 3:
		GameData::reset(false);
		CCDirector::sharedDirector()->resume();
		CCDirector::sharedDirector()->replaceScene(GameScene::scene());
		break;
	case 4:
		GameData::reset(false);
		CCDirector::sharedDirector()->resume();
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
		CCDirector::sharedDirector()->replaceScene(SelectScene::scene());
		break;
	case 5:
		GameData::reset(false);
		CCDirector::sharedDirector()->resume();
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
		CCDirector::sharedDirector()->replaceScene(StartScene::scene());
		break;
	}
}

void GameScene::showPauseLayer(bool show){
	if(show){
		if(!pauseLayer){
			pauseLayer = CCLayer::create();
			CCSprite* bg = CCSprite::create("dlg_long.png");
			SETANCHPOS(bg,0,0,0,0);
			pauseLayer->addChild(bg);

			CCMenu* menu = CCMenu::create();
			SETANCHPOS(menu,0,0,0,0);
			pauseLayer->addChild(menu);

			CCMenuItemSprite* play = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("play.png"),
				CCSprite::createWithSpriteFrameName("play.png"),this,menu_selector(GameScene::btnCallback));
			play->setTag(2);
			SETANCHPOS(play,200,25,0,0);
			menu->addChild(play);

			CCMenuItemSprite* retry = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("retry.png"),
				CCSprite::createWithSpriteFrameName("retry.png"),this,menu_selector(GameScene::btnCallback));
			SETANCHPOS(retry,350,25,0,0);
			retry->setTag(3);
			menu->addChild(retry);

			CCMenuItemSprite* back = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("back.png"),
				CCSprite::createWithSpriteFrameName("back.png"),this,menu_selector(GameScene::btnCallback));
			SETANCHPOS(back,500,25,0,0);
			back->setTag(4);
			menu->addChild(back);

			CCMenuItemSprite* main = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("menu.png"),
				CCSprite::createWithSpriteFrameName("menu.png"),this,menu_selector(GameScene::btnCallback));
			SETANCHPOS(main,650,25,0,0);
			main->setTag(5);
			menu->addChild(main);

			addChild(pauseLayer,15);
		}
	}else{
		removeChild(pauseLayer,true);
		pauseLayer = NULL;
	}
}