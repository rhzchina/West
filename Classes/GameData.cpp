#include "GameData.h"

GameData* GameData::instance = NULL;

GameData::GameData(void)
{
	level = 1;
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

