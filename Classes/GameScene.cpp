#include "GameScene.h"
GameScene::GameScene(void)
{
	scrollBg1 = NULL;
	scrollBg = NULL;
	bgX = 0;
	speed = 0.5;
	map = NULL;
	hero = NULL;
	overText = NULL;

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

		overText = CCLabelTTF::create("Game OVer!!!\nTouch screen to replay,Let's go","黑体",30);
		overText->setColor(ccc3(255,0,0));
		overText->setPosition(ccp(425,240));
		overText->setVisible(false);

		CC_BREAK_IF(!scrollBg);
		//CC_BREAK_IF(!scrollBg1);
		CC_BREAK_IF(!sky);

		addChild(sky,-3);
		addChild(scrollBg,-2);
		addChild(overText,1);
		//addChild(scrollBg1);
		scrollBg->setAnchorPoint(ccp(0,0));
		//scrollBg1->setAnchorPoint(ccp(0,0));
		
		sky->setPosition(ccp(sky->getContentSize().width/2,CCDirector::sharedDirector()->getWinSize().height - sky->getContentSize().height / 2));
		scrollBg->setPosition(ccp(0,0));
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
		CCDirector::sharedDirector()->replaceScene(GameScene::scene());
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
}

