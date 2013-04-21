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

	static void setGold(int g){instance->gold = g;}
	static int getGold(){return instance->gold;}

	static void setSate(int type,int state,int v){instance->itemState[type][state] = v;}
	static int getState(int type,int state){return instance->itemState[type][state];}
private:
	GameData(void);
	int level;
	int gold;
	int itemState[4][2];  //商店物品的使用情况，用二维数组记录，第一个表示已解锁，第二个表示正在使用
	static GameData* instance;
};
#endif                                                    