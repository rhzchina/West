#ifndef WELCOME_H
#define WELCOME_H
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class WelcomeScene : public CCLayer
{
public:
	static const int WEAPON = 1;
	static const int TREASURE = 2;
	static const int TIP = 3;
	static const int CLOTHES = 4;

	WelcomeScene(void);
	~WelcomeScene(void);

	bool init();
	static CCScene* scene();
	CREATE_FUNC(WelcomeScene);

	void btnCallback(CCObject*);
	void createItems(int);
private:
	CCScrollView* scroll;
	CCLayer* itemsLayer;
	CCLabelAtlas* goldNum;

};

#endif