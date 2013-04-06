#ifndef WELCOME_H
#define WELCOME_H
#include "cocos2d.h"
USING_NS_CC;

class WelcomeScene : public CCLayer
{
public:
	WelcomeScene(void);
	~WelcomeScene(void);
	bool init();
	static CCScene* scene();
	CREATE_FUNC(WelcomeScene);

};

#endif