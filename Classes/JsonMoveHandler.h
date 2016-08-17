#pragma once
#include "cocos2d.h"
//#include "Constant.h"
#include <vector>

class JsonMoveHandler :public cocos2d::Ref
{
public:
	JsonMoveHandler();
	~JsonMoveHandler();
	static JsonMoveHandler* GetInstance();
	bool ParseJson(std::string file_path);
	cocos2d::Sequence* GenerateAction();
	float GetRand(float range,float offset);
	cocos2d::FiniteTimeAction* CreatOneAction(cocos2d::Vec2 position,float time,int effect);

	std::vector<cocos2d::Vec2> position_vec;
	std::vector<float> time_vec;
	std::vector<std::string> effect_vec;
	std::vector<float> random_vec;
private:
	static JsonMoveHandler* m_phandler;
};

