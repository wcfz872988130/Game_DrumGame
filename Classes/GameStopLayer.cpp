#include "GameStopLayer.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

bool GameStopLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}

cocos2d::Layer* GameStopLayer::createLayer()
{
	return GameStopLayer::create();
}
