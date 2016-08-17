#include "Home.h"
#include "GameScene.h"
#include "DataUtils.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

bool Home::init()
{
	if(!Layer::init())
	{
		return false;
	}

	// 创建根节点
	auto rootNode = CSLoader::createNode("scenes/Home-scene.csb");
	addChild(rootNode);

	// 创建动画
	auto action = CSLoader::createTimeline("scenes/Home-scene.csb");
	rootNode->runAction(action);

	// 播放动画
	action->gotoFrameAndPlay(0, 45, false);

	auto redLeft = static_cast<Sprite*>(rootNode->getChildByName("red_left"));
	auto redRight = static_cast<Sprite*>(rootNode->getChildByName("red_right"));

	auto btnLeft = static_cast<Button*>(rootNode->getChildByName("btn-left"));
	auto btnRight = static_cast<Button*>(rootNode->getChildByName("btn-right"));

	auto btnAction = Sequence::create(
		FadeOut::create(1),
		FadeIn::create(1.2),
		NULL);
	auto btnAction2 = Sequence::create(
		FadeOut::create(1),
		FadeIn::create(1.2),
		NULL);
	btnLeft->runAction(RepeatForever::create(btnAction));
	btnRight->runAction(RepeatForever::create(btnAction2));

	btnLeft->addTouchEventListener(CC_CALLBACK_1(Home::btnLeftCallback, this));
	btnRight->addTouchEventListener(CC_CALLBACK_1(Home::btnRightCallback, this));

	return true;
}

cocos2d::Scene* Home::createScene()
{
	auto layer = Home::create();
	auto scene = Scene::create(); 
	scene->addChild(layer);
	return scene;
}

void Home::btnLeftCallback(cocos2d::Ref* pSender)
{
	DataUtils::save(DataType::GameType, "Touch");  // 触屏方式
	//Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5, GameScene::createScene()));
    Director::getInstance()->replaceScene(GameScene::createScene());
}

void Home::btnRightCallback(cocos2d::Ref* pSender)
{
	DataUtils::save(DataType::GameType, "Pat");    // 拍打方式
	//Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5, GameScene::createScene()));
    Director::getInstance()->replaceScene(GameScene::createScene());
}
