#include "Map.h"


Map::Map(void)
{
	map = NULL;
	mapUp = false;                                                          
	int array[] = {1, 2, 6, 2, 3, 0, 4, 0, 0, 6, 0, 0, 0, 1, 2,
		3, 0,0, 5, 0,7,8,9};
	mapData = vector<int>();
	for(int i = 0;i < sizeof(array)/sizeof(array[0]);i++){
		mapData.push_back(array[i]);
	}

}

Map::~Map(void)
{
}

void Map::initMap(int level){
	float x = 0;
	float y = 0;
	switch(level){
	case 1:
		map = CCArray::createWithCapacity(9);
		map->retain();
		for(int i = 0;i <mapData.size();i++){
			if(mapData.at(i)!=0){    //陆地
				char buf[30];
				sprintf(buf,"land1_%d.png",mapData[i]);
				CCSprite* land = CCSprite::create(buf);
				land->setAnchorPoint(ccp(0,0));
				if(mapData.at(i)==6){   //顶部陆地
					y = 480 - land->getContentSize().height; 
					CCLog("%f,%f",CCDirector::sharedDirector()->getWinSize().height,land->getContentSize().height);
					land->setPosition(ccp(x,y));

				}else{  
					CCSprite* startLand = NULL;
					if(map->count() >= 1){
						startLand = (CCSprite*)map->objectAtIndex(0);
					}

					if(mapData.at(i)==7){
						y = -(land->getContentSize().height - startLand->getContentSize().height);
					}else if(mapData.at(i)==8){
						x-=72;
						y = -(land->getContentSize().height - startLand->getContentSize().height + 75);
					}else if(mapData.at(i) == 9){
						x-=68;
						y = -(land->getContentSize().height - startLand->getContentSize().height+75+131);
					}else{
						y = 0;
					}
					land->setPosition(ccp(x,y));
					x += land->getContentSize().width;
				}
				map->addObject(land);
			}else{   //空地
				x += 100;
			}
		}
		break;
	case 2:
		break;
	case 3:
		break;
	}
}

void Map::addMap(CCLayer* layer){
	if(map != NULL){
		for(int i = 0;i < map->count();i++){
			layer->addChild((CCSprite*)map->objectAtIndex(i));
		}
	}

}

bool Map::onLand(CCSprite* hero){
	bool onLand = false;
	for(int i = 0;i < map->count();i++){
		CCSprite* temp = (CCSprite*)map->objectAtIndex(i);
		if(temp->getPosition().x < hero->getPositionX() + hero->getContentSize().width / 2){
			if(CCRectMake(temp->getPositionX(),temp->getPositionY(),temp->getContentSize().width,temp->getContentSize().height).
				intersectsRect(CCRectMake(hero->getPositionX(),hero->getPositionY() - hero->getContentSize().height / 2,
				hero->getContentSize().width / 2,hero->getContentSize().height))){
					onLand = true;
			}
		}
	}
	return onLand;

}

void Map::mapMove(){
	for(int i = 0;i < map->count();i++){
		CCSprite* m = (CCSprite*)map->objectAtIndex(i);
		if(m->getPositionX()+m->getContentSize().width>= 0){
			float x = m->getPositionX();
			float y = m->getPositionY();
			if(mapUp){
				CCLog("start ");
			}else{
				x-=4;
			}
			/*if(!mapUp && i >= map->count() - 3){
			if(i == map->count() - 1){
			y += 50;
			mapUp = true;
			}else{
			y += 50;
			}
			}*/
			m->setPosition(ccp(x,y));
		}else{
			map->removeObjectAtIndex(i);
			m->removeFromParentAndCleanup(true);
		}
	}
}