#pragma once
/**
 * 首页主菜单
 */
#include <cocos2d.h>
#include <cocostudio/CocoStudio.h>
#include <ui/CocosGUI.h>

class Home : public cocos2d::Layer
{
public:
	virtual bool init() override;
	static cocos2d::Scene* createScene();
	CREATE_FUNC(Home);
	
	void btnLeftCallback(cocos2d::Ref* pSender);
	void btnRightCallback(cocos2d::Ref* pSender);
}; 