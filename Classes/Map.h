#ifndef MAP_H
#define MAP_H
#include "cocos2d.h"
#include <vector>
#include "Role.h"
using namespace std;
USING_NS_CC;
class GameScene;

class Map
{
public:
	Map(int,GameScene*);
	~Map(void);
	void initMap(int);
	void addMap(GameScene*);
	void mapMove(GameScene*,Role* );
	bool onLand(CCSprite*);
	bool weaponOn(Role*);
	int getSpeed(){return speed;}
	void createData(int);
	void resetMap(int,GameScene*);
	int getLevel(){return curLevel;}
private:
	CCArray* map;
	vector<int> mapData;
	bool mapUp;
	float speed; 
	int curLevel;
};

#endif