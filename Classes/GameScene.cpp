#include "GameScene.h"
GameScene::GameScene(void)
{
	scrollBg1 = NULL;
	scrollBg = NULL;
	bgX = 0;
	speed = 0.5;
	map = NULL;
	hero = NULL;
}


GameScene::~GameScene(void)
{

}

bool GameScene::init(){
	bool bRet = false;
	do{
		CC_BREAK_IF(!CCLayer::init());
		setTouchEnabled(true);

		scrollBg = CCSprite::create("bg2.jpg");
		//scrollBg1 = CCSprite::createWithTexture(scrollBg->getTexture());
		sky = CCSprite::create("tian1.jpg");

		CC_BREAK_IF(!scrollBg);
		//CC_BREAK_IF(!scrollBg1);
		CC_BREAK_IF(!sky);

		addChild(sky);
		addChild(scrollBg);
		//addChild(scrollBg1);
		scrollBg->setAnchorPoint(ccp(0,0));
		//scrollBg1->setAnchorPoint(ccp(0,0));
		
		sky->setPosition(ccp(sky->getContentSize().width/2,CCDirector::sharedDirector()->getWinSize().height - sky->getContentSize().height / 2));
		scrollBg->setPosition(ccp(0,0));
		//scrollBg1->setPosition(ccp(scrollBg->getContentSize().width,0));
		//初始化地图
		map = new Map(1);
		map->addMap(this);
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

	CCLog("(%f,%f)",location.x,location.y);

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
	map->mapMove();
	if(hero->getSprite()->getPositionY() < 130){
		if(map->onLand(hero->getSprite())){
			if(hero->getState() != Role::FALL && hero->getState() != Role::ATTACK){
				hero->changeState(Role::NORMAL);
			}else if(hero->getState() == Role::ATTACK){
				hero->hold();
			}
		}
	}else if(hero->getSprite()->getPositionY() == 130){
		if(!map->onLand(hero->getSprite())) {
			hero->fall();
		 }
	}

	if(map->weaponOn(hero)){
		hero->weaponDone(map->getSpeed(),dt);
	}
}

