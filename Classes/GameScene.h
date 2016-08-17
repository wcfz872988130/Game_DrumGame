#pragma once
#include <cocos2d.h>
#include <cocostudio/CocoStudio.h>
#include <ui/CocosGUI.h>
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include <leaf.h>

//code for test by Young
#include "DropObject.h"
//code for test by Young
// 场景背景类型
enum SCENE_TYPE
{
	SCENE_RED,
	SCENE_YELLOW,
	SCENE_GREEN,
	SCENE_PURPLE,
	SCENE_CHRISTMAS,
	SCENE_LOAD,
};

class GameScene : public cocos2d::Layer
{
public:
	virtual bool init() override;
	static cocos2d::Scene* createScene();
	cocos2d::Vector<cocos2d::Sprite*>  _vec;
	SCENE_TYPE sceneType;
	Leaf* AALeaf = new Leaf();

	// 切换场景
	void changeBackground(SCENE_TYPE bgType);

	// 场景动画
	// 说明 ： 场景动画部分由csb提供，部分由代码提供
	bool animationRedScene();
	bool animationYellowScene();
	bool animationGreenScene();
	bool animationPurpleScene();
	bool animationChristmasScene();
	bool animationLoadScene();
	CREATE_FUNC(GameScene);
	void update(float dt);

	//code for test by Young
	bool onTouchBegan(cocos2d::Touch* tTouch, cocos2d::Event* eEvent);//手指按下事件
	void onTouchMoved(cocos2d::Touch* tTouch, cocos2d::Event* eEvent);//手指移动事件
	void onTouchEnded(cocos2d::Touch* tTouch, cocos2d::Event* eEvent);//手指离开事件
	void SpriteMoveUpdate(float dt);
	void CollisonDetectionUpdate(float dt);
	void DestinationRemoveUpdate(float dt);
    void GateIntervalUpdate(float dt);
	void ShowHitFeedback(HitType type, cocos2d::Vec2 position);
	void InitTimeArray();
	void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event);
	void LoadGameScene();
	void MoveAction(float dt);
	void SnowDrop(float dt);
    void menuCloseCallback(cocos2d::Ref* pSender);
    //code for test by Young
	
private:
	Node* rootNode;
	cocos2d::Sprite* cloud_1;
	cocos2d::Sprite* cloud_2;
	cocos2d::Sprite* cloud_3;
	cocos2d::Sprite* tree_1;
	cocos2d::Sprite* tree_2;
	cocos2d::Sprite* tree_3;
	cocos2d::Sprite* tree_4;
	cocos2d::Sprite* drop;
	cocos2d::Sprite* star;
	cocos2d::Sprite* snow1;
	cocos2d::Sprite* snow2;
	cocos2d::Sprite* snow3;
	cocos2d::Sprite* snow4;
	cocos2d::Sprite* deer;
	cocos2d::Size visibleSize;

	//code for test by Young
	float m_count;
	int m_array_index;
	bool m_collison_detection_switch;
	bool m_acceleration_switch;
    bool m_interval_switch;
    float m_interval_count;
    float m_pre_accz;
	cocos2d::Vector<DropObject*> m_sprite_vec;
	//code for test by Young
	float dropPosition;

};
