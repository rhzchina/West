#include "Role.h"
#include "tool.h"
#include "GameData.h"


Role::Role(CCLayer* parent)
{
	int index = GameData::getState(CLOTHES).at(0);
	char plist[20];
	char name[20];
	sprintf(plist,"hero%d.plist",index);
	sprintf(name,"hero%d.png",index);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist,name);
	CCSpriteFrame* prepare = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("run_1.png");
	hero = CCSprite::createWithSpriteFrame(prepare);
	hero->setPosition(ccp(POSX,POSY));

	index = GameData::getState(WEAPON).at(0);
	sprintf(name,"weapon/weapon%d.png",index);
	weapon = Weapon::create(name,hero);
	parent->addChild(this);   //英雄对象也加入管理
	parent->addChild(weapon);
	parent->addChild(hero,11);
	state = 0;
	protecting = false;
	die = false;
	changeState(NORMAL);
}


Role::~Role(void)
{
	delete hero;
	hero = NULL;
}

void Role::setProtect(bool b){
	protecting = b;
}

void Role::nextLevel(){
	protecting = false;
	changeState(JUMP);
	hero->runAction(CCMoveTo::create(1,ccp(POSX,0)));
}

void Role::jump(){
	if(hero){
		if(state == NORMAL){
			changeState(JUMP);
			hero->runAction(CCSequence::create(CCJumpTo::create(1,ccp(hero->getPositionX(),0),200,1),
				CCCallFunc::create(this,callfunc_selector(Role::actionCallback))
				,NULL));
		}else if(state == JUMP){
			weapon->shoot();
			state = WAIT;
		}
	}
}

void Role::hold(){
	if(state == ATTACK){
		hero->setPositionY(hero->getPositionY() + 10);
		changeState(HOLD);
		int height = 350  - hero->getPositionY() > 0 ? 350 - hero->getPositionY() : 0;
		float time = height / 200.0f; 
		hero->runAction(CCSequence::create(CCJumpTo::create(time < 0.5 ? 0.5 : time,ccp(hero->getPositionX(),0),height,1),
			CCCallFunc::create(this,callfunc_selector(Role::actionCallback))
			,NULL));
	}
}

void Role::resetWeapon(){
	weapon->reset();
}

void Role::actionCallback(){
	if(state == JUMP || state == WAIT){
		if(state == JUMP){
			CCLog("GAME Over");
		}
		changeState(NORMAL);
	}else if(state == ATTACK ){
		hold();
	}else if(state == HOLD){
		changeState(NORMAL);
	}else if(state == OVER){
		changeState(FLY);
	}else if(state == FALL){
		die = true;
		hero->stopAllActions();
	}
}

void Role::weaponDone(int speed,float frameTime){
	state = ATTACK;
	weapon->stopAllActions();
	float time = POINT_INSTANCE(ccp(0,weapon->getPositionY()),ccp(weapon->getPositionX(),weapon->getPositionY())) / (speed / frameTime); 
	weapon->runAction(CCMoveTo::create(time,ccp(0,weapon->getPositionY())));
}

void Role::fall(){
	if(!protecting && state != FALL){
		state = FALL;
		hero->runAction(CCSequence::create(CCMoveTo::create(0.2f,ccp(hero->getPositionX(),0)),CCCallFunc::create(this,callfunc_selector(Role::actionCallback)),NULL));
	}
}

//over参数指定是否是一关结束的飞行
void Role::fly(bool over){
	if(state != OVER && state != FLY){
	if(over){
		changeState(JUMP);
		state = OVER;
	}
	hero->runAction(CCSequence::create(CCJumpTo::create(1,ccp(POSX,300),100,1),CCCallFunc::create(this,callfunc_selector(Role::actionCallback)),NULL));
	}
}

void Role::changeState(int s){
	if(state == ATTACK){
		resetWeapon();
	}
	state = s > HOLD  ? NORMAL : s;
	hero->stopAllActions();
	int count = 0;
	char* name = NULL; 
	switch(state){
	case NORMAL:
		count = 5;
		name = "run_%d.png";
		hero->setPositionY(130);
		break;
	case SPEEDUP:
		count = 4;
		name = "speedup_%d.png";
		break;
	case FLY:
		count = 3;
		name = "fly_%d.png";
		break;
	case JUMP:
		count = 1;
		name = "jump_%d.png";
		break;
	case HOLD:
		count = 3;
		name = "hold_%d.png";
		break;
	}
	CCArray* frames = CCArray::createWithCapacity(count);
	CCSpriteFrame* frame = NULL;
	for(int i = 0;i < frames->capacity();i++){
		char buf[30];
		sprintf(buf,name,(i+1));
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf);
		frames->addObject(frame);
	}
	CCAnimate* ani = CCAnimate::create(CCAnimation::createWithSpriteFrames(frames,0.1f));
	hero->runAction(CCRepeatForever::create(ani));
}

CCRect Role::getWeaponRange(){
	return CCRectMake(weapon->getPositionX() + weapon->getContentSize().width / 2,weapon->getPositionY(),
		weapon->getContentSize().width / 2,weapon->getContentSize().height / 2);
}