#ifndef ROLE_H
#define ROLE_H
#include "cocos2d.h"
#include "Weapon.h"
USING_NS_CC;
class Role : public CCNode 
{
public:
	static const int NORMAL = 0;
	static const int SPEEDUP = 1;
	static const int FLY = 2;
	static const int JUMP = 3;
	static const int WAIT = 4;  //跳起投出武器，当武器飞行时人物不可操作状态
	static const int ATTACK = 5;
	static const int HOLD = 6;
	static const int FALL = 7;

	Role(CCLayer*);
	~Role(void);
	void changeState(int);
	int getState(){return state;}
	CCSprite* getSprite(){return hero;}
	void jump(CCPoint);
	void hold();
	void actionCallback();
	void checkWeaponSchedule(float );
	void fall();
	void resetWeapon();
private:
	int state;
	bool checkOnLand;
	CCSprite* hero;
	Weapon* weapon;
};
#endif