#include "Map.h"


Map::Map(int level)
{
	map = NULL;
	mapUp = false;                                                          
	mapData = vector<int>();
	createData(level);
	speed = 5;
	initMap(1);
}

Map::~Map(void)
{
}

void Map::createData(int level){
	if(level == 1){
		int array[] = {1, 2, 6, 2, 3, 0, 4, 0	, 0, 6, 0, 0, 0, 1, 2,
			3, 0,0, 5, 0,7,8,9};
		for(int i = 0;i < sizeof(array)/sizeof(array[0]);i++){
			mapData.push_back(array[i]);
		}
	}else if(level == 2){
		int array[] =  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 6, 2, 3, 0, 5, 0, 5, 0, 4, 0, 0, 6, 0, 0, 0, 1, 2, 3,
			0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0 };
		for(int i = 0;i < sizeof(array)/sizeof(array[0]);i++){
			mapData.push_back(array[i]);
		}
	}else if(level == 3){
		int array[] =  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 6, 2, 6, 2, 3, 0, 4, 0, 0, 6, 0, 0, 0, 1, 3, 0, 5, 0,
			1, 3, 0, 5, 0, 1, 3, 0, 5, 0, 1, 3, 0, 5, 0, 1, 3, 0, 5, 0, 1, 3, 0, 5, 0, 1, 3, 0, 5, 0 };
		for(int i = 0;i < sizeof(array)/sizeof(array[0]);i++){
			mapData.push_back(array[i]);
		}
	}else if(level == 4){
		int array[] =  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 6, 2, 3, 0, 4, 0, 0, 6, 0, 0, 0, 1, 2, 3, 0, 0, 6, 0, 0, 0, 1, 3, 0, 0, 6, 0, 0,
			0, 1, 3, 0, 5, 0, 0, 6, 0, 0, 0, 1, 3, 0, 5, 0, 1, 2, 6, 2, 3, 0, 5, 0, 4, 0 };
		for(int i = 0;i < sizeof(array)/sizeof(array[0]);i++){
			mapData.push_back(array[i]);
		}
	}else if(level == 5){
		int array[] =  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 6, 2, 3, 0, 4, 0, 0, 6, 0, 0, 0, 1, 2, 3, 0, 5, 0, 5,
			0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0 };
		for(int i = 0;i < sizeof(array)/sizeof(array[0]);i++){
			mapData.push_back(array[i]);
		}
	}else if(level == 6){
		int array[] =  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 6, 2, 3, 0, 4, 0, 0, 6, 0, 0, 0, 1, 3, 0, 5, 0, 1, 3,
			0, 5, 0, 1, 3, 0, 5, 0, 1, 3, 0, 5, 0, 1, 3, 0, 5, 0, 1, 3, 0, 5, 0, 1, 3, 0, 5, 0 };
		for(int i = 0;i < sizeof(array)/sizeof(array[0]);i++){
			mapData.push_back(array[i]);
		}
	}else if(level == 7){
		int array[] =  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 6, 2, 3, 0, 4, 0, 0, 6, 0, 0, 0, 1, 2, 3, 0, 5, 0, 5,
			0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0 };
		for(int i = 0;i < sizeof(array)/sizeof(array[0]);i++){
			mapData.push_back(array[i]);
		}
	}else if(level == 8){
		int array[] =  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 6, 2, 3, 0, 4, 0, 0, 6, 0, 0, 0, 1, 2, 3, 0, 0, 6, 0,
			0, 0, 1, 3, 0, 5, 0, 0, 6, 0, 0, 0, 1, 2, 3, 1, 2, 6, 2, 3, 0, 5, 0, 4, 0 ,7,8,9};
		for(int i = 0;i < sizeof(array)/sizeof(array[0]);i++){
			mapData.push_back(array[i]);
		}
	}else if(level == 9){
		int array[] =  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 6, 2, 3, 0, 4, 0, 0, 6, 0, 0, 0, 1, 2, 3, 0, 0, 6, 0,
			0, 0, 1, 3, 0, 5, 0, 0, 6, 0, 0, 0, 1, 2, 3,0, 1, 2, 6, 2, 3, 0, 5, 0, 4, 0,7,8,9 };
		for(int i = 0;i < sizeof(array)/sizeof(array[0]);i++){
			mapData.push_back(array[i]);
		}
	}else if(level == 10){
		int array[] = {1,3, 0,7,8,9};
		for(int i = 0;i < sizeof(array)/sizeof(array[0]);i++){
			mapData.push_back(array[i]);
		}
	}
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
					land->setPosition(ccp(x,y));

				}else{  
					CCSprite* startLand = NULL;
					if(map->count() >= 1){
						startLand = (CCSprite*)map->objectAtIndex(0);
					}

					if(mapData.at(i)==7){
						y = -(land->getContentSize().height - startLand->getContentSize().height + 55);
						land->setTag(7);
					}else if(mapData.at(i)==8){
						x-=195;
						y = -(land->getContentSize().height - startLand->getContentSize().height + 30 + 50);
						land->setTag(8);
					}else if(mapData.at(i) == 9){
						x-=135;
						y = -(land->getContentSize().height - startLand->getContentSize().height+30+35 + 115);
						land->setTag(9);
					}else{
						y = -55;
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

bool Map::weaponOn(Role* hero){
	bool shootOn = false;
	if(hero->getState() == Role::WAIT ){
		for(int i = 0; i < map->count();i++){
			CCSprite* temp = (CCSprite*)map->objectAtIndex(i);
			if(temp->getPositionY() > 240){
				if(hero->getWeaponRange().intersectsRect(CCRectMake(temp->getPositionX(),temp->getPositionY(),
					temp->getContentSize().width,temp->getContentSize().height))){
						shootOn = true;
						break;
				}
			}
		}
	} 
	return shootOn;
}

void Map::mapMove(){
	for(int i = 0;i < map->count();i++){
		CCSprite* m = (CCSprite*)map->objectAtIndex(i);

		if(m->getPositionX() > 854){
			m->setVisible(false);
		}
		if(m->getPositionX()+m->getContentSize().width>= 0){
			float x = m->getPositionX();
			float y = m->getPositionY();
			if(mapUp){
				if(m->getTag() >= 7 ){
					switch(m->getTag()){
					case 7:
						if(y<-55){
							y+=speed / 2.0f;
						}
						break;
					case 8:
						if(y < -75){
							y+=speed / 2.0f;
						}
						break;
					case 9:
						if(y < -70){
							y+=speed / 2.0f;
						}
						break;
					}
				}else{
					if( y < 0){
						y += speed;
					}
				}
				x -= speed / 1.5f;
			}else{
				x-=speed;
			}
			//一关结束的地图向上移动
			if(!mapUp && i >= map->count() - 3){
				if(m->getPositionX() + 100 < 200){
					mapUp = true;
				}
			}

			m->setPosition(ccp(x,y));
			if(m->getPositionX() < 854){
				m->setVisible(true);
			}
		}else{
			map->removeObjectAtIndex(i);
			m->removeFromParentAndCleanup(true);
		}


	}
}