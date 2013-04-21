                                                                                                         #include "GameData.h"

GameData* GameData::instance = NULL;

GameData::GameData(void)
{
	level = 1;
	gold = 2;
	//memset(itemState,0,sizeof(itemState));
	
	itemState[0][0] = 1;
	itemState[1][0] = 2;
	itemState[2][0] = 3;
	itemState[3][0] = 4;

	itemState[0][1] = 1;
	itemState[1][1] = 1;
	itemState[2][1] = 1;
	itemState[3][1] = 1;
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

                                                                                                                                                                                                                                                                                                                                                                                                                