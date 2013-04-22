#ifndef GAMEDATA_H
#define GAMEDATA_H
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

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
	static void addGold(int change){instance->gold += change;}

	static void addSate(int type,int state,int v){instance->data[type].push_back(v);}
	static void replaceSate(int type,int v){instance->data[type][0] = v;}
	static bool bought(int type,int id);
	static vector<int> getState(int type){return instance->data[type];}

	static void addScore(int s){instance->score += s;}
	static int getScore(){return instance->score;}

	static void addDistance(int d){instance->distance += d;}
	static int getDistance(){return instance->distance;}
		
	static int getBest(){return instance->best;}
	static void reset(bool all);

	static void addLoop(){instance->loopCount++;}
	static long getLoop(){return instance->loopCount;}
private:
	GameData(void);
	int level;
	int gold;
	int score;
	int distance;
	int best;
	int itemState[4][2];  //�̵���Ʒ��ʹ��������ö�ά�����¼����һ����ʾ�ѽ������ڶ�����ʾ����ʹ��
	vector<int> data[4];
	long loopCount;  //ѭ������
	static GameData* instance;
};
#endif                                                    