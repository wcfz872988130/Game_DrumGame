#include "Splash.h"
#include "Home.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

bool Splash::init()
{
	if(!Layer::init())
	{
		return false;
	}

	// 创建根节点
	m_RootNode = CSLoader::createNode("scenes/Splash-scene.csb");
	addChild(m_RootNode);

	// 创建动画
	m_Action = CSLoader::createTimeline("scenes/Splash-scene.csb");
	m_RootNode->runAction(m_Action);

	// hide star
	Sprite* left_m = static_cast<Sprite*>(m_RootNode->getChildByName("left-m"));
	left_m->setVisible(false);

	Sprite* center_m = static_cast<Sprite*>(m_RootNode->getChildByName("center-m"));
	center_m->setVisible(false);

	Sprite* center_down = static_cast<Sprite*>(m_RootNode->getChildByName("center-down"));
	center_down->setVisible(false);

	Sprite* left_up = static_cast<Sprite*>(m_RootNode->getChildByName("left-up"));
	left_up->setVisible(false);

	Sprite* right_up = static_cast<Sprite*>(m_RootNode->getChildByName("right-up"));
	right_up->setVisible(false);

	Sprite* center_up = static_cast<Sprite*>(m_RootNode->getChildByName("center-up"));
	center_up->setVisible(false);

	this->scheduleUpdate();
	// 播放动画
	m_Action->gotoFrameAndPlay(0, 150, false);

	// 动画最后一帧回调
	m_Action->setLastFrameCallFunc(CC_CALLBACK_0(Splash::onFrameEvent, this));
	
	return true;
}

cocos2d::Scene* Splash::createScene()
{
	auto layer = Splash::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	return scene;
}

void Splash::update(float delta)
{
	auto index = m_Action->getCurrentFrame();

	// left-m sprite fadein and fadeout
	if (index == 1)
	{
		Sprite* left_m = static_cast<Sprite*>(m_RootNode->getChildByName("left-m"));
		left_m->setVisible(true);
		left_m->runAction(FadeIn::create(0.5f));
	}
	if (index == 35)
	{
		Sprite* left_m = static_cast<Sprite*>(m_RootNode->getChildByName("left-m"));
		left_m->runAction(FadeOut::create(0.5f));
	}

	// center-m sprite fadein and fadeout
	if (index == 35)
	{
		Sprite* center_m = static_cast<Sprite*>(m_RootNode->getChildByName("center-m"));
		center_m->setVisible(true);
		center_m->runAction(FadeIn::create(0.5f));
	}
	if (index == 45)
	{
		Sprite* center_m = static_cast<Sprite*>(m_RootNode->getChildByName("center-m"));
		center_m->runAction(FadeOut::create(0.5f));
	}

	// center-down fadein and fadeout
	if (index == 50)
	{
		Sprite* center_down = static_cast<Sprite*>(m_RootNode->getChildByName("center-down"));
		center_down->setVisible(true);
		center_down->runAction(FadeIn::create(0.5f));
	}
	if (index == 70)
	{
		Sprite* center_down = static_cast<Sprite*>(m_RootNode->getChildByName("center-down"));
		center_down->runAction(FadeOut::create(0.5f));
	}

	// left-up fadein and fadeout
	if (index == 90)
	{
		Sprite* left_up = static_cast<Sprite*>(m_RootNode->getChildByName("left-up"));
		left_up->setVisible(true);
		left_up->runAction(FadeIn::create(0.5f));
	}
	if (index == 120)
	{
		Sprite* left_up = static_cast<Sprite*>(m_RootNode->getChildByName("left-up"));
		left_up->runAction(FadeOut::create(0.5f));
	}

	// right-up fadein and fadeout
	if (index == 90)
	{
		Sprite* right_up = static_cast<Sprite*>(m_RootNode->getChildByName("right-up"));
		right_up->setVisible(true);
		right_up->runAction(FadeIn::create(0.5f));
	}
	if (index == 108)
	{
		Sprite* right_up = static_cast<Sprite*>(m_RootNode->getChildByName("right-up"));
		right_up->runAction(FadeOut::create(0.5f));
	}

	// center-up fadein and fadeout
	if (index == 90)
	{
		Sprite* center_up = static_cast<Sprite*>(m_RootNode->getChildByName("center-up"));
		center_up->setVisible(true);
		center_up->runAction(FadeIn::create(0.5f));
	}
	if (index == 130)
	{
		Sprite* center_up = static_cast<Sprite*>(m_RootNode->getChildByName("center-up"));
		center_up->runAction(FadeOut::create(0.4f));
	}
}

void Splash::onFrameEvent()
{
	Director::getInstance()->replaceScene(Home::createScene());
}
