#ifndef SELECTSCENE_H
#define SELECTSCENE_H
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameData.h"
#include "GameScene.h"
USING_NS_CC;
USING_NS_CC_EXT;

class SelectScene : public CCLayer
{
public:
	const static int MAXLEVEL = 4;
	SelectScene(void);
	~SelectScene(void);
	CREATE_FUNC(SelectScene);

	bool init();
	static CCScene* scene();

	void ccTouchesBegan(CCSet*,CCEvent*);
	void ccTouchesMoved(CCSet*,CCEvent*);
	void ccTouchesEnded(CCSet*,CCEvent*);
	

	int touchedLevel(CCPoint);
	void btnCallback(CCObject*);

private:
	CCScrollView* scroll;
	CCArray* level;
	CCLabelTTF* tipText;
	int touched;
	float lastX;
};
#endif