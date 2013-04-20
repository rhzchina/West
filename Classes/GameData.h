#ifndef GAMEDATA_H
#define GAMEDATA_H
#include "cocos2d.h"
USING_NS_CC;
class GameData
{
public:
	static GameData* getInstance();
	~GameData();
	static int getLevel();
	static	void addLevel();
	static void setLevel(int);

	static int getGold(){return instance->gold;}
	static void setGold(int g){instance->gold = g;}
private:
	GameData(void);
	int level;
	int gold;
	static GameData* instance;
};
#endif