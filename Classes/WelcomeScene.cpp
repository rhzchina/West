#include "WelcomeScene.h"


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

		CCSprite* sky = CCSprite::create("ylcbt.png");
		sky->setAnchorPoint(ccp(0,1));
		sky->setPosition(ccp(0,480));	
		addChild(sky);

		CCSprite* bg = CCSprite::create("bg1.png");
		bg->setAnchorPoint(ccp(0,0));
		addChild(bg);


		int x = 0;
		int y = 300;
		CCSprite* temp = NULL;
		for (int i = 0;i <= 6; i++)
		{
			char buf[30];
			sprintf(buf,"hero_%d.png",i);
			temp = CCSprite::create(buf);
			temp->setAnchorPoint(ccp(0,0));
			temp->setPosition(ccp(x,y));
			x += temp->getContentSize().width + 20;
			if(i < 3){
				y -= 80;
			}else{
				y += 80;
			}
			addChild(temp);
		}

		
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
