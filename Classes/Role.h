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
	static const int OVER = 8;

	static const int POSX = 200;
	static const int POSY = 130;
	Role(CCLayer*);
	~Role(void);
	void changeState(int);
	int getState(){return state;}
	CCSprite* getSprite(){return hero;}
	void jump();
	void hold();
	void actionCallback();
	void fall();
	void fly(bool);
	void resetWeapon();
	CCRect getWeaponRange();
	void weaponDone(int,float);  //武器击中
	void setProtect(bool);
	bool isProtected(){return protecting;}
	void nextLevel();
	bool isDie(){return die;}
private:
	bool protecting;   //无敌状态
	int state;
	bool checkOnLand;
	CCSprite* hero;
	Weapon* weapon;
	bool die;  
};
#endif