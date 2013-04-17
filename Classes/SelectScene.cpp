#include "SelectScene.h"
#include "tool.h"

SelectScene::SelectScene(void)
{
	scroll = NULL;
	level = NULL;
}


SelectScene::~SelectScene(void)
{
}

bool SelectScene::init(){
	bool success = false;
	do{
		CCLayer::init();

		setTouchEnabled(true);

		GameData::getInstance();
		CCSprite* bg = CCSprite::create("startBg.jpg");
		CC_BREAK_IF(!bg);
		SETANCHPOS(bg,0,0,0,0);
		addChild(bg);

		CCLayer* container = CCLayer::create();
		CC_BREAK_IF(!container);
		SETANCHPOS(container,0,0,0,0);

		int x = 0;
		level = CCArray::createWithCapacity(MAXLEVEL);
		level->retain();
		for(int i = 1;i <= MAXLEVEL;i++){
			char name[20];
			sprintf(name,"level%d.png",i);
			CCSprite* item = CCSprite::create(name);
			SETANCHPOS(item,x,240,0,0.5);
			CC_BREAK_IF(!item);
			container->addChild(item);
			level->addObject(item);
			x += item->getContentSize().width * 1.5f;
		}
		container->setContentSize(CCSizeMake(2400,480));

		scroll = CCScrollView::create();
		CC_BREAK_IF(!scroll);
		SETANCHPOS(scroll,0,0,0,0);
		scroll->setViewSize(CCSizeMake(854,480));
		scroll->setContentSize(CCSizeMake(2400,480));
		scroll->setContainer(container);
		scroll->setDirection(kCCScrollViewDirectionHorizontal);
		addChild(scroll);

		success = true;
	}while(0);
	return success;
}

CCScene* SelectScene::scene(){
	CCScene* scene = NULL;
	do{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);

		SelectScene* layer = SelectScene::create();
		CC_BREAK_IF(!layer);
		
		scene->addChild(layer);
	}while(0);

	return scene;
}

 void SelectScene::ccTouchesBegan(CCSet* touches,CCEvent* event){
	CCTouch* touch = (CCTouch*)touches->anyObject();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
	int num = touchedLevel(location);
	if(num != -1){
		touched = num;
		lastX = location.x;
	}

}

void SelectScene::ccTouchesMoved(CCSet* touches,CCEvent* event){
	CCTouch* touch = (CCTouch*)touches->anyObject();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
	if(abs(lastX - location.x) > 50){
		touched = -1;
	}
}

void SelectScene::ccTouchesEnded(CCSet* touches,CCEvent* event){
	CCTouch* touch = (CCTouch*)touches->anyObject();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
	int num = touchedLevel(location);
	if (num != -1 && num == touched){
		GameData::setLevel(num);
		CCDirector::sharedDirector()->replaceScene(GameScene::scene());
	}else{
		touched = -1;
	}

}

int SelectScene::touchedLevel(CCPoint pos){
	int num = -1;
	for(int i = 0;i < level->count();i++)	{
		CCSprite* t = (CCSprite*)level->objectAtIndex(i);
		if(CCRectMake(scroll->getContentOffset().x + t->getPositionX(),t->getPositionY() - t->getContentSize().height / 2,
			t->getContentSize().width,t->getContentSize().height).containsPoint(pos)){
			num = i + 1;
		}
	}
	return num;
	
}