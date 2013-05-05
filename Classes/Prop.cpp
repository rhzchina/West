#include "Prop.h"
#include "tool.h"


Prop::Prop(int type, CCLayer* parent, float x, float y)
{
	char name[50];
	switch(type){
	case SCORE:
		switch(rand() % 4){
		case 0:
			sprintf(name,"peach.png");
			break;
		case 1:
			sprintf(name,"dragon_scale.png");
			break;
		case 2:
			sprintf(name,"fire.png");
			break;	
		case 3:
			sprintf(name,"bamboo.png");
			break;
		}
		prop = CCSprite::createWithSpriteFrameName(name);
		break;
	case PROP:
		prop = CCSprite::createWithSpriteFrameName("random.png");
		break;
	}
	SETANCHPOS(prop, x, y, 0, 0.5);
	parent->addChild(prop);
}


Prop::~Prop(void)
{
	prop->removeFromParentAndCleanup(true);

	prop = NULL;
}

bool Prop::move(float speed){
	bool remove = false;
	prop->setPositionX(prop->getPositionX() - speed);
	if(prop->getPositionX() + prop->getContentSize().width < 0){
		remove = true;
	}
	return remove;
}