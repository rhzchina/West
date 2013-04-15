#include "SelectScene.h"
#include "tool.h"

SelectScene::SelectScene(void)
{
	scroll = NULL;
}


SelectScene::~SelectScene(void)
{
}

bool SelectScene::init(){
	bool success = false;
	do{
		CCLayer::init();

		CCSprite* bg = CCSprite::create("startBg.jpg");
		CC_BREAK_IF(!bg);
		SETANCHPOS(bg,0,0,0,0);
		addChild(bg);

		CCLayer* container = CCLayer::create();
		CC_BREAK_IF(!container);
		SETANCHPOS(container,0,0,0,0);

		int x = 0;
		for(int i = 1;i <= 4;i++){
			char name[20];
			sprintf(name,"level%d.png",i);
			CCSprite* item = CCSprite::create(name);
			SETANCHPOS(item,x,240,0,0.5);
			CC_BREAK_IF(!item);
			container->addChild(item);
			x += item->getContentSize().width * 1.5f;
		}
		scroll = CCScrollView::create();
		CC_BREAK_IF(!scroll);
		SETANCHPOS(scroll,0,0,0,0);
		scroll->setViewSize(CCSizeMake(854,480));
		scroll->setContentSize(CCSizeMake(2000,480));
		scroll->setContainer(container);
		scroll->setDirection(CCScrollViewDirection::kCCScrollViewDirectionHorizontal);
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