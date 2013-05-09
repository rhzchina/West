#ifndef PROP_H
#define PROP_H
#include "cocos2d.h"
USING_NS_CC;

class Prop : public CCObject
{
public:
	static const int SCORE = 1;
	static const int PROP = 2;
	
	Prop(int type, CCLayer* parent,float x, float y);
	~Prop();

	bool move(float speed);
	float getPosX(){return prop->getPositionX();}
private:
	CCSprite* prop;
};

#endif