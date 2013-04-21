                                                                                                         #include "GameData.h"

GameData* GameData::instance = NULL;

GameData::GameData(void)
{
	level = 1;
	gold = 99999999;
	score = 0;
	distance = 0;
	best = 0;
	//memset(itemState,0,sizeof(itemState));
	
	itemState[0][0] = 0;
	itemState[1][0] = 0;
	itemState[2][0] = 0;
	itemState[3][0] = 0;

	itemState[0][1] = 0;
	itemState[1][1] = 0;
	itemState[2][1] = 0;
	itemState[3][1] = 0;
}

GameData::~GameData(void)
{
}

GameData* GameData::getInstance(){
	if(instance == NULL){
		instance = new GameData();
	}
	return instance;
}

void GameData::addLevel(){
	instance->level++;
	if(instance->level > 4){
		instance->level = 1;
	}
}

void GameData::setLevel(int l){
	instance->level = l;
}

int GameData::getLevel(){
	return instance->level;
}

void GameData::reset(bool all){
	if(all){
		instance->best = 0;
	}else{
		instance->best = instance->distance;		
	}
	instance->score = 0;
	instance->distance = 0;
	
}
                                                                                                                                                                                                                                                                                                                                                                                                                