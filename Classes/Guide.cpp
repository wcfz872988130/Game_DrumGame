#include "Guide.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

bool Guide::init()
{
	if(!Layer::init())
	{
		return false;
	}

	// 创建根节点
	auto rootNode = CSLoader::createNode("scenes/Guide-scene.csb");
	addChild(rootNode);

	// 创建动画
	auto action = CSLoader::createTimeline("scenes/Guide-scene.csb");
	rootNode->runAction(action);

	// 播放动画
	action->gotoFrameAndPlay(0, 30, false);

	return true;
}

cocos2d::Scene* Guide::createScene()
{
	auto layer = Guide::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	return scene;
}
