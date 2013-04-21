#include "SelectScene.h"
#include "StartScene.h"
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

		CCSprite* bg = CCSprite::create("shopBg.jpg");
		CC_BREAK_IF(!bg);
		SETANCHPOS(bg,0,0,0,0);
		addChild(bg);

		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("choose.plist","choose.png");

		CCLayer* container = CCLayer::create();
		CC_BREAK_IF(!container);
		SETANCHPOS(container,0,50,0,0);

		int x = 0;
		level = CCArray::createWithCapacity(MAXLEVEL);
		level->retain();
		for(int i = 1;i <= MAXLEVEL;i++){
			//Ñ¡¹Ø±³¾°
			CCSprite* itemBg = CCSprite::create("choose_bg.png");
			SETANCHPOS(itemBg,x + 930 / 2,240,0.5,0.5);
			container->addChild(itemBg);

			//Ñ¡¹ØÃû³Æ±³¾°
			CCSprite* nameBg = CCSprite::createWithSpriteFrameName("name_bg.png");
			SETANCHPOS(nameBg,x + 854 / 2 - itemBg->getContentSize().width / 2,240,0.5,0.5);
			container->addChild(nameBg);

			char name[20];
			//¹Ø¿¨Ãû³Æ
			sprintf(name,"level%d_name.png",i);
			CCSprite* levelName = CCSprite::createWithSpriteFrameName(name);
			SETANCHPOS(levelName,x + 854 / 2 - itemBg->getContentSize().width / 2,240,0.5,0.5);
			container->addChild(levelName);
			
			sprintf(name,"level%d.png",i);
			CCSprite* item = CCSprite::create(name);
			SETANCHPOS(item,x + 930 / 2,255,0.5,0.5);
			CC_BREAK_IF(!item);
			container->addChild(item);
			level->addObject(item);
			x += 854;
		}
		container->setContentSize(CCSizeMake(854 * 4,480));

		scroll = CCScrollView::create();
		CC_BREAK_IF(!scroll);
		SETANCHPOS(scroll,0,0,0,0);
		scroll->setViewSize(CCSizeMake(854,480));
		scroll->setContentSize(CCSizeMake(854 * 4,480));

		scroll->setContainer(container);
		scroll->setDirection(kCCScrollViewDirectionHorizontal);
		addChild(scroll);

		CCMenu* menu = CCMenu::create();
		SETANCHPOS(menu,0,0,0,0);
		addChild(menu);

		CCMenuItemImage* back = CCMenuItemImage::create("back.png","back.png",this,menu_selector(SelectScene::btnCallback));
		SETANCHPOS(back,740,380,0,0);
		back->setTag(1);
		menu->addChild(back);

		//ÃèÊö±³¾°
		CCSprite* desBg = CCSprite::create("dlg_short.png");
		SETANCHPOS(desBg,425,0,0.5,0);
		addChild(desBg);

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
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
		CCDirector::sharedDirector()->replaceScene(GameScene::scene());
	}else{
		touched = -1;
	}

}

int SelectScene::touchedLevel(CCPoint pos){
	int num = -1;
	for(int i = 0;i < level->count();i++)	{
		CCSprite* t = (CCSprite*)level->objectAtIndex(i);
		if(CCRectMake(scroll->getContentOffset().x + t->getPositionX() - t->getContentSize().width / 2,t->getPositionY() - t->getContentSize().height / 2,
			t->getContentSize().width,t->getContentSize().height).containsPoint(pos)){
			num = i + 1;
		}
	}
	return num;
	
}

void SelectScene::btnCallback(CCObject* sender){
	switch(((CCNode*)sender)->getTag()){
	case 1:
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
		CCDirector::sharedDirector()->replaceScene(StartScene::scene());
		break;
	case 2:
		break;
	}
}