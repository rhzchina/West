#ifndef MAP_H
#define MAP_H
#include "cocos2d.h"
#include <vector>
using namespace std;
USING_NS_CC;
class Map
{
public:
	Map(void);
	~Map(void);
	void initMap(int);
	void addMap(CCLayer*);
	void mapMove();
	bool onLand(CCSprite*);

private:
	CCArray* map;
	vector<int> mapData;
	bool mapUp;
};

#endif