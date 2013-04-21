#include "ShopItem.h"
#include "GameData.h"
#include "tool.h"

ShopItem::ShopItem(int x,int y,const char* name,int v,int type, int id)
{
	layer = CCLayer::create();
	SETANCHPOS(layer,x,y,0,0);

	CCSprite* bg = CCSprite::createWithSpriteFrameName("item_bg.png");
	SETANCHPOS(bg,0,0,0,0);
	layer->addChild(bg);

	layer->setContentSize(bg->getContentSize());

	CCSprite* item = CCSprite::create(name);
	//SETANCHPOS(item,x + bg->getContentSize().width / 2,0,0.5,0);
	SETANCHPOS(item,bg->getContentSize().width / 2 ,bg->getContentSize().height / 2,0.5,0);
	layer->addChild(item);

	value = v;
	this->type = type;
	this->id = id;

	if (GameData::getState(type,0) < id){ //����Ʒ��δ���� 
		char str[20];
		sprintf(str,"%d",v);
		CCLabelAtlas* valueText = CCLabelAtlas::create(str,"num/num_yellow.png",28,40,'0');

		SETANCHPOS(valueText,bg->getContentSize().width / 2,20,0.5,0);
		layer->addChild(valueText);
	}else{  //����Ʒ�ѹ���
		char* str = conv("����");
		ccColor3B color = ccc3(255,0,0);
		if(GameData::getState(type,1) == id){ // ��Ʒ����ʹ��
			CCSprite* use = CCSprite::createWithSpriteFrameName("use.png");
			SETANCHPOS(use,bg->getContentSize().width / 2, bg->getContentSize().height / 2,0.5,0);
			layer->addChild(use);
			str = conv("��ʹ��");
			color = ccc3(0,255,0);
		}
		CCLabelTTF* text = CCLabelTTF::create(str,"Arial",30);
		text->setColor(color);
		SETANCHPOS(text,bg->getContentSize().width / 2 ,25,0.5,0);
		layer->addChild(text);


	}
}


ShopItem::~ShopItem(void)
{
}

bool ShopItem::isTouch(float x, float y){
	if(CCRectMake(layer->getPositionX(),layer->getPositionY(),
		layer->getContentSize().width,layer->getContentSize().height).containsPoint(ccp(x,y))){
			return true;
	}
	return false;
}

int ShopItem::touchAction(){
	if(GameData::getState(type,0) < id ){
		return -1;  //���ɲ���
		CCLog("this equip has not bought");
	}else{
		CCLog("this equip can be use");
		GameData::setSate(type,1,id); //��������Ϊ��ǰװ��
		return 0;  //����װ��
	}
}