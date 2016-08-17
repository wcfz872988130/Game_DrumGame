#pragma once
/**
 * 游戏暂停画面层
 */
#include <cocos2d.h>
#include <cocostudio/CocoStudio.h>
#include <ui/CocosGUI.h>

class GameStopLayer : public cocos2d::Layer
{
public:
	virtual bool init() override;
	static cocos2d::Layer* createLayer();
	CREATE_FUNC(GameStopLayer);
};
