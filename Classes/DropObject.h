#pragma once
#include "cocos2d.h"

// picture path of sprites
static const char* type_one_path = "game_scene/animal1.png";
static const char* type_two_path = "game_scene/animal2.png";

// 精灵类型
enum DropType
{
	TYPE_ONE,
	TYPE_TWO,
	UNKNOWN
};

// 拍击结果
enum HitType
{
	MISS,
	GOOD,
	PERFECT
};

// 运动方式
enum MoveType
{
	LINE,
	COS
};

class DropObject : public cocos2d::Sprite
{
public:
	DropObject();
	~DropObject();
	virtual bool init(DropType type);

	static DropObject* createObject(DropType type);

	HitType JudgeHit(const float radius, cocos2d::Vec2 center);

	void Move(cocos2d::Vec2 circle_center,cocos2d::Vec2 destination, float duration1,float duration2, MoveType type);

	void MoveInLine(cocos2d::Vec2 circle_center, cocos2d::Vec2 destination, float duration1, float duration2);

	void MoveInCos(cocos2d::Vec2 circle_center, cocos2d::Vec2 destination, float duration1, float duration2);

private:
	bool m_isAlive;       // 是否存活
	DropType m_dropType;  // 精灵类型
	Sprite* m_sprite ;
};