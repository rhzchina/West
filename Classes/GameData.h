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
	int itemState[4][2];  //�̵���Ʒ��ʹ��������ö�ά�����¼����һ����ʾ�ѽ������ڶ�����ʾ����ʹ��
	static GameData* instance;
};
#endif                                                    