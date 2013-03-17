#ifndef WEAPON_H
#define WEAPON_H
#include "cocos2d.h"


USING_NS_CC;
class Weapon : public CCSprite
{

public:
	static Weapon* create(const char *,CCSprite*);

	Weapon(void);
	~Weapon(void);
	void shoot(CCPoint);
	void draw();
	void reset();
	void actionCallback();

	bool isShootDone(){return shootDone;}
private:

	CCSprite* owner;
	bool shootDone;  //»÷ÖÐ¸¡Ê¯

};
#endif