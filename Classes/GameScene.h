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

	void btnCallback(CCObject*);
	void showPauseLayer(bool);
	void addSpeed(float add){speed += add;}
	void setProgress(float percent){progressLeaf->setPositionX(progressBg->getPositionX() + percent *  progressBg->getContentSize().width) ;}
	static CCScene* scene();
	CREATE_FUNC(GameScene);
private:
	CCSprite* scrollBg;
	CCSprite* scrollBg1;
	CCSprite* sky;
	CCSprite* progressBg;
	CCSprite* progressLeaf;
	Map* map;
	Role* hero;
	float bgX;
	float speed;
	CCLayer* pauseLayer;
	CCLayer* items;
	CCLabelTTF* overText;
	CCLabelAtlas* scoreValue;
	CCLabelAtlas* distanceValue;
	CCLabelAtlas* bestValue;
};
#endif