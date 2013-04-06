#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "cocos2d.h"
#include "Map.h"
#include "Role.h"

USING_NS_CC;
class GameScene : public CCLayer 
{
public:
	GameScene(void);
	~GameScene(void);

	bool init();
	void initBgItems(int);
	void bgMove(float);
	void ccTouchesBegan(CCSet* ,CCEvent*);
	void ccTouchesMoved(CCSet*,CCEvent*);
	void ccTouchesEnded(CCSet*,CCEvent*);

	void addSpeed(float add){speed += add;}
	static CCScene* scene();
	CREATE_FUNC(GameScene);
private:
	CCSprite* scrollBg;
	CCSprite* scrollBg1;
	CCSprite* sky;
	Map* map;
	Role* hero;
	float bgX;
	float speed;
	CCLabelTTF* overText;
	CCLayer* items;
};
#endif