#include "DropObject.h"

using namespace cocos2d;

// –Ë µœ÷π¶ƒ‹
// ∏˘æ› ±º‰–Ú¡–≤˙…˙∂Øª≠,¬‰µΩ‘≤»¶÷––ƒ
// ≈–∂œ≈ƒª˜ ±µƒŒ«∫œ∂»£¨prefect£¨good£¨miss


DropObject::DropObject()
	: m_isAlive(true), m_dropType(DropType::UNKNOWN), m_sprite(nullptr)
{
}

DropObject::~DropObject()
{
	
}

//–Ë µœ÷π¶ƒ‹
//∏˘æ› ±º‰–Ú¡–≤˙…˙∂Øª≠,¬‰µΩ‘≤»¶÷––ƒ
//≈–∂œ≈ƒª˜ ±µƒŒ«∫œ∂»£¨prefect£¨good£¨miss
bool DropObject::init(DropType type)
{
	if (!Sprite::init())
	{
		return false;
	}

	m_dropType = type;
	switch (m_dropType)
	{
	case TYPE_ONE:
		m_sprite = Sprite::create(type_one_path);
		break;
	case TYPE_TWO:
		m_sprite = Sprite::create(type_two_path);
		break;
	default:
		m_sprite = Sprite::create(type_one_path);
		break;
	}

	m_sprite->setPosition(Vec2(0, 0));
	this->addChild(m_sprite);
	return true;
}

DropObject* DropObject::createObject(DropType type)
{
	DropObject* pRet = new(std::nothrow) DropObject();
	if (pRet && pRet->init(type))
	{
		pRet->autorelease();
		return pRet;
	} 
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

HitType DropObject::JudgeHit(const float radius, const Vec2 center)
{
	Vec2 position = this->getPosition();
	HitType hit_type;
	float distance = sqrt((position.x - center.x)*(position.x - center.x) + (position.y - center.y)*(position.y - center.y));
	if (distance < radius / 2)
	{
		hit_type = PERFECT;
	}
	else if (distance < radius)
	{
		hit_type = GOOD;
	}
	else
	{
		hit_type = MISS;
	}
	return hit_type;
}

void DropObject::Move(Vec2 circle_center,Vec2 destination, float duration1,float duration2, MoveType type)
{
	switch (type)
	{
	case LINE:
		MoveInLine(circle_center, destination,  duration1, duration2);
		break;
	case COS:
		MoveInCos(circle_center, destination, duration1, duration2);
		break;
	default:
		break;
	}
}

void DropObject::MoveInLine(cocos2d::Vec2 circle_center, cocos2d::Vec2 destination, float duration1, float duration2)
{
	auto move_line_1 = MoveTo::create(duration1, circle_center);
	auto move_line_2 = MoveTo::create(duration2, destination);
	auto remove_self_line = RemoveSelf::create();
	auto sequence_line = Sequence::create(move_line_1,move_line_2, nullptr);
	this->runAction(sequence_line);
}

void DropObject::MoveInCos(cocos2d::Vec2 circle_center, cocos2d::Vec2 destination, float duration1, float duration2)
{
	auto jump_cos = JumpTo::create(duration1, circle_center,1,1);
	auto move_cos = MoveTo::create(duration2, destination);
	//auto remove_self_cos = RemoveSelf::create();
	auto sequence_cos = Sequence::create(jump_cos, move_cos,nullptr);
	this->runAction(sequence_cos);
}
