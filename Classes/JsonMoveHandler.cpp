#include "JsonMoveHandler.h"
#include "cocostudio/CocoStudio.h"

#include <cstdlib>

using namespace cocos2d;
extern float left_circle_radius;
extern Vec2 left_circle_center;

JsonMoveHandler* JsonMoveHandler::m_phandler = nullptr;

JsonMoveHandler* JsonMoveHandler::GetInstance()
{
	if (m_phandler == nullptr)
	{
		m_phandler = new JsonMoveHandler();
		CCASSERT(m_phandler,"Fail to get instance!");
	}
	return m_phandler;
}

bool JsonMoveHandler::ParseJson(std::string file_path)
{
	rapidjson::Document open_doc;
	bool bRet = false;
	ssize_t size = 0;
	unsigned char *pBytes = nullptr;
	//these once execute sentences can use "break" to interrupt "loop", that's the difference
	do {
		//to read the json file
		pBytes = cocos2d::FileUtils::getInstance()->getFileData("Json/test.json", "r", &size);
		CC_BREAK_IF(pBytes == nullptr || strcmp((char*)pBytes, "") == 0);

		std::string load_str((const char*)pBytes, size);

		CC_SAFE_DELETE_ARRAY(pBytes);
		open_doc.Parse<0>(load_str.c_str());
		CCASSERT(!open_doc.HasParseError(), "Parse error!");
		CC_BREAK_IF(open_doc.HasParseError());
		
		//生成json文档对像  
		if (!open_doc.IsObject())
			return false;

		//是否有此成员  
		if (!open_doc.HasMember("descriptions"))
			return false;

		// 通过[]取成员值,再根据需要转为array,int,double,string  
		const rapidjson::Value &pArray = open_doc["descriptions"];

		//是否是数组  
		if (!pArray.IsArray())
			return false;

		for (rapidjson::SizeType i = 0; i < pArray.Size(); i++)
		{
			const rapidjson::Value &p = pArray[i];
			if (i == pArray.Size() - 1)
			{
				const rapidjson::Value &valueEnt = p["random"];
				if (valueEnt.HasMember("pos_random") && valueEnt.HasMember("time_random")
					&& valueEnt.HasMember("effect_random"))
				{
					const rapidjson::Value &pos_random = valueEnt["pos_random"];
					float pos_rand = pos_random.GetDouble();
					random_vec.push_back(pos_rand);

					const rapidjson::Value &time_random = valueEnt["time_random"];
					float time_rand = time_random.GetDouble();
					random_vec.push_back(time_rand);

					const rapidjson::Value &effect_random = valueEnt["effect_random"];
					float effect_rand = effect_random.GetDouble();
					random_vec.push_back(effect_rand);
				}
			}
			if (p.HasMember("description"))
			{
				const rapidjson::Value &valueEnt = p["description"];
				if (valueEnt.HasMember("xpos") && valueEnt.HasMember("ypos") 
					&& valueEnt.HasMember("time")&&valueEnt.HasMember("effect"))
				{
					const rapidjson::Value &xpos = valueEnt["xpos"];
					float x_pos = (float)xpos.GetDouble();      

					const rapidjson::Value &ypos = valueEnt["ypos"];
					float y_pos = (float)ypos.GetDouble(); 
					position_vec.push_back(Vec2(x_pos, y_pos));

					const rapidjson::Value &time = valueEnt["time"];
					float f_time = time.GetDouble();  
					time_vec.push_back(f_time);

					const rapidjson::Value &effect = valueEnt["effect"];
					std::string s_effect = effect.GetString();   
					effect_vec.push_back(s_effect);

				}
			}
			else
			{
				return false;
			}
			
		}
		bRet = true;
	} while (0);
	//for json
}

JsonMoveHandler::JsonMoveHandler()
{
}

JsonMoveHandler::~JsonMoveHandler()
{
	delete m_phandler;
	m_phandler = nullptr;
}

//每个精灵从起点到终点的时间固定为2秒
Sequence* JsonMoveHandler::GenerateAction()
{
	cocos2d::Vector<FiniteTimeAction *> action_vec;
	int size = position_vec.size();
	for (int i = 0; i < size - 1; i++)
	{
		float posx = left_circle_center.x;// +GetRand(2 * random_vec.at(0), random_vec.at(0));
		float time = time_vec.at(i);//+ GetRand(20, 10) / 100;
		int effect_index = (int)GetRand(5.0, 0.0);
		float posy = position_vec.at(i).y + GetRand(2 * random_vec.at(0), random_vec.at(0));
		action_vec.pushBack(CreatOneAction(Vec2(posx, posy), time, effect_index));
	}
	//must ensure finally reach the destination, the circle
	float posx = position_vec.at(size-1).x;
	float time = time_vec.at(size - 1); //+ GetRand(20, 10) / 100;
	int effect_index = (int)GetRand(5.0, 0.0);
	float posy = position_vec.at(size-1).y;
	action_vec.pushBack(CreatOneAction(Vec2(posx, posy), time, effect_index));
	
	action_vec.pushBack(MoveTo::create(1.0f, left_circle_center - Vec2(0, 2 * left_circle_radius)));
	auto sequence = Sequence::create(action_vec);
	return sequence;
}

FiniteTimeAction* JsonMoveHandler::CreatOneAction(cocos2d::Vec2 position, float time, int effect)
{
	if (effect == 0)
	{
		auto move = MoveTo::create(time, position);
		return move;
	}
	else if (effect==1)
	{
		auto move = MoveTo::create(time, position);
		auto scale_min = ScaleTo::create(time*0.5, 0.5);
		auto scale_origin = ScaleTo::create(time*0.5, 1);
		auto sequence = Sequence::createWithTwoActions(scale_min, scale_origin);
		auto spawn = Spawn::createWithTwoActions(move, sequence);
		return spawn;
	}
	else if (effect==2)
	{
		cocos2d::ccBezierConfig config;
		config.endPosition = position;
		config.controlPoint_1 = Vec2(480, 320);
		config.controlPoint_2 = Vec2(480, 320);
		auto bezier = BezierTo::create(time,config);
		return bezier;
		/*auto jump = JumpTo::create(time, position, 50, 3);
		return jump;*/
	}
	else if (effect==3)
	{
		auto move = MoveTo::create(time, position);
		auto blink = Blink::create(time, 5);
		auto spawn = Spawn::createWithTwoActions(move, blink);
		return spawn;
	}
	else
	{
		auto move = MoveTo::create(time, position);
		auto tint = TintBy::create(time, 100,100,100);
		auto spawn = Spawn::createWithTwoActions(move, tint);
		return spawn;
	}
}

float JsonMoveHandler::GetRand(float range, float offset)
{
	//获取系统时间
	struct timeval now;
	gettimeofday(&now, NULL);

	//初始化随机种子
	//timeval是个结构体，里边有俩个变量，一个是以秒为单位的，一个是以微妙为单位的 
	unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000);    //都转化为毫秒 
	srand(rand_seed);
	float answer = rand() % ((int)range) - offset;
	return answer;
}



