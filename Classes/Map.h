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
	Map(int);
	~Map(void);
	void initMap(int);
	void addMap(CCLayer*);
	void mapMove();
	bool onLand(CCSprite*);
	bool weaponOn(Role*);
	int getSpeed(){return speed;}
	void createData(int);
private:
	CCArray* map;
	vector<int> mapData;
	bool mapUp;
	int speed; 
};

#endif