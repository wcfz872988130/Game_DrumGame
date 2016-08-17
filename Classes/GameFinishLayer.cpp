#include "GameFinishLayer.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

bool GameFinishLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}

cocos2d::Layer* GameFinishLayer::createLayer()
{
	return GameFinishLayer::create();
}
