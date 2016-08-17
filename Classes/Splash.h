#pragma once
/**
 * 启动画面
 */
#include <cocos2d.h>
#include <cocostudio/CocoStudio.h>
#include <ui/CocosGUI.h>

class Splash : public cocos2d::Layer
{
public:
	virtual bool init() override;
	static cocos2d::Scene* createScene();
	void update(float delta);
	CREATE_FUNC(Splash);

	// frame event callback
	void onFrameEvent();

private:
	cocostudio::timeline::ActionTimeline* m_Action;
	cocos2d::Node* m_RootNode;
};
