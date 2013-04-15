#ifndef SELECTSCENE_H
#define SELECTSCENE_H
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class SelectScene : public CCLayer
{
public:
	SelectScene(void);
	~SelectScene(void);
	CREATE_FUNC(SelectScene);

	bool init();
	static CCScene* scene();

private:
	CCScrollView* scroll;
};
#endif