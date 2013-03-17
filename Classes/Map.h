#ifndef MAP_H
#define MAP_H
#include "cocos2d.h"
#include <vector>
#include "Role.h"
using namespace std;
USING_NS_CC;
class Map
{
public:
	Map(int,CCLayer*);
	~Map(void);
	void initMap(int);
	void addMap(CCLayer*);
	void mapMove(CCLayer*,Role* );
	bool onLand(CCSprite*);
	bool weaponOn(Role*);
	int getSpeed(){return speed;}
	void createData(int);
	void resetMap(int,CCLayer*);
	int getLevel(){return curLevel;}
private:
	CCArray* map;
	vector<int> mapData;
	bool mapUp;
	int speed; 
	int curLevel;
};

#endif