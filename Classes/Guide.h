#pragma once
/**
 * 引导动画
 */
#include <cocos2d.h>
#include <cocostudio/CocoStudio.h>
#include <ui/CocosGUI.h>

class Guide : public cocos2d::Layer
{
public:
	virtual bool init() override;
	static cocos2d::Scene* createScene();
	CREATE_FUNC(Guide);
};
