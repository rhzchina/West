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
		this->setZOrder(100);
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
	CCTouch* touch = (CCTouch*)touches->anyObject();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
	hero->jump();
	if(hero->isDie()){
		CCDirector::sharedDirector()->replaceScene(StartScene::scene());
	}
}

void GameScene::ccTouchesMoved(CCSet* touches,CCEvent* event){

}

void GameScene::ccTouchesEnded(CCSet* touches,CCEvent* event){
	hero->hold();
}

void GameScene::bgMove(float dt){
	//bgX -= speed;
	//if(bgX <= -scrollBg->getContentSize().width){
	//	bgX = 0;
	//}
	//scrollBg->setPositionX(bgX)	;
	//scrollBg1->setPositionX(bgX+scrollBg->getContentSize().width);
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

