#include "GameScene.h"
#include "Home.h"

//code for test by Young
#include "DropObject.h"
#include "Constant.h"
#include "JsonMoveHandler.h"
#include "Audio.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

//code for test by Young

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();

	/*
	// create game scene
	// 创建根节点
	rootNode = CSLoader::createNode("scenes/Game-scene.csb");
	addChild(rootNode);

	// 创建动画
	auto action = CSLoader::createTimeline("scenes/Game-scene.csb");
	rootNode->runAction(action);

	// 播放动画
	action->gotoFrameAndPlay(0, 30, false);
	*/

	LoadGameScene();
	//animationRedScene();
	//animationYellowScene();
    //string normal =FileUtils::getInstance()->fullPathForFilename("fanhui.png").c_str();
    //string selected =FileUtils::getInstance()->fullPathForFilename("fanhui.png").c_str();
    
    auto closeItem = MenuItemImage::create("game_finish/fanhui.png","game_finish/fanhui.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    closeItem->setPosition(Point(visibleSize.width - closeItem->getContentSize().width / 2,
                                 closeItem->getContentSize().height / 2));
	//code added by Young
	Audio::getInstance()->playBackground("audio/Kanon.wav");
	InitTimeArray();

	auto label = LabelTTF::create("ACC", "arial", 40);
	label->setColor(Color3B(255, 255, 255));
	label->setPosition(visibleSize.width / 2, visibleSize.height - 20);
	//this->addChild(label, 1, "label");

	Device::setAccelerometerEnabled(true);
	auto acc_listener = EventListenerAcceleration::create(CC_CALLBACK_2(GameScene::onAcceleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(acc_listener, this);

	/*auto draw = DrawNode::create();
	draw->drawCircle(left_circle_center, left_circle_radius, 0, 100, false, 1.0, 1.0, Color4F(255, 0, 0, 125));
	draw->drawCircle(right_circle_center, right_circle_radius, 0, 100, false, 1.0, 1.0, Color4F(255, 0, 0, 125));
	this->addChild(draw);*/
	//code added by Young

	//code for test by Young
	//JsonMoveHandler* handler = JsonMoveHandler::GetInstance();
	//handler->ParseJson(json_file_path);

	m_count = 0.0f;
	m_array_index = 0;
	m_collison_detection_switch = false;
	m_acceleration_switch = false;
    m_interval_switch = false;
    m_interval_count=0.0;
    m_pre_accz=-1.0;

	this->schedule(schedule_selector(GameScene::SpriteMoveUpdate), 1.0f / 60, CC_REPEAT_FOREVER, 0);
	this->schedule(schedule_selector(GameScene::CollisonDetectionUpdate), 1.0f / 60, CC_REPEAT_FOREVER, 0);
	this->schedule(schedule_selector(GameScene::DestinationRemoveUpdate), 1.0f / 60, CC_REPEAT_FOREVER, 0);
    this->schedule(schedule_selector(GameScene::GateIntervalUpdate), 1.0f / 100, CC_REPEAT_FOREVER, 0);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//rootNode->getChildByName("");
	//code for test by Young
	return true;
}

void GameScene::onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event)
{
	//stringstream sstream;
    float accz =acc->z;
	//sstream << accz;
	//LabelTTF* label = (LabelTTF*)getChildByName("label");
	//label->setString(sstream.str());
    
	if (accz > gate_accz&&accz-m_pre_accz>accz_delta&&m_interval_switch&& m_acceleration_switch == false)
	{
		m_acceleration_switch = true;
        m_interval_switch=false;
        m_interval_count=0.0;
    }
    m_pre_accz=accz;
}

void GameScene::GateIntervalUpdate(float dt)
{
    if (m_interval_count>=gate_interval)
    {
        m_interval_switch = true;
    }
    else
    {
        m_interval_count = m_interval_count+dt;
    }
}

void GameScene::InitTimeArray()
{
    string str=FileUtils::getInstance()->fullPathForFilename("simple_time.txt").c_str();
    //string str=FileUtils::getInstance()->fullPathForFilename("freshhand_time.txt").c_str(); //新手
	ifstream fin(str);
	if (!fin)
	{
		cout << "File open error!\n";
		return;
	}
	int time;
	int count = 0;
	while ((time = fin.get()) != EOF)
	{
		fin >> time;
		timeArray[count] = time / 1000.0f;
		count++;
	}
	fin.close();
}

cocos2d::Scene* GameScene::createScene()
{
	auto layer = GameScene::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	return scene;
}

void GameScene::changeBackground(SCENE_TYPE bgType)
{

}

void GameScene::LoadGameScene()
{
	rootNode = CSLoader::createNode("scenes/GameScene-1.csb");
	this->addChild(rootNode);

	Sprite* left_guandao = static_cast<Sprite*>(rootNode->getChildByName("guidao_2"));
	Sprite* left_circle = static_cast<Sprite*>(left_guandao->getChildByName("Node_1"));
	left_circle_radius = left_guandao->getContentSize().width / 2;
	left_circle_center.x = left_guandao->getPositionX();
	left_circle_center.y = left_guandao->getPositionY() - left_guandao->getContentSize().height / 2 + left_circle->getPositionY();
	

	Sprite* right_guandao = static_cast<Sprite*>(rootNode->getChildByName("guidao_2_0"));
	Sprite* right_circle = static_cast<Sprite*>(right_guandao->getChildByName("Node_1"));
	right_circle_radius = right_guandao->getContentSize().width / 2;
	right_circle_center.x = right_guandao->getPositionX();
	right_circle_center.y = right_guandao->getPositionY() - right_guandao->getContentSize().height / 2 + right_circle->getPositionY();

   

}

bool GameScene::animationRedScene()
{
	rootNode = CSLoader::createNode("scenes/Red-Scene.csb");
	this->addChild(rootNode);

	Sprite* start_1 = static_cast<Sprite*>(rootNode->getChildByName("start_1_1"));
	auto fadeOut = FadeOut::create(3);
	auto fadeOutReverse = fadeOut->reverse();
	auto Sequencefade_1 = Sequence::create(fadeOut, fadeOutReverse, NULL);
	auto repeatfade = RepeatForever::create(Sequencefade_1);
	start_1->runAction(repeatfade);

	Sprite* start_2 = static_cast<Sprite*>(rootNode->getChildByName("start_1_2"));
	auto delay = DelayTime::create(0.5);
	auto Sequencefade_2 = Sequence::create(delay,fadeOut,fadeOutReverse,NULL);
	auto repeatfade_2 = RepeatForever::create(Sequencefade_2);
	start_2->runAction(repeatfade_2);

	Sprite* start_3 = static_cast<Sprite*>(rootNode->getChildByName("start_2_1"));
	auto delay_1 = DelayTime::create(1.0);
	auto Sequencefade_3 = Sequence::create(delay_1, fadeOut, fadeOutReverse, NULL);
	auto repeatfade_3 = RepeatForever::create(Sequencefade_3);
	start_3->runAction(repeatfade_3);

	Sprite* start_4 = static_cast<Sprite*>(rootNode->getChildByName("start_2_2"));
	auto delay_2 = DelayTime::create(1.5);
	auto Sequencefade_4 = Sequence::create(delay_2, fadeOut, fadeOutReverse, NULL);
	auto repeatfade_4 = RepeatForever::create(Sequencefade_4);
	start_4->runAction(repeatfade_4);

	cloud_1 = static_cast<Sprite*>(rootNode->getChildByName("cloud_1_1"));	
	cloud_2 = static_cast<Sprite*>(rootNode->getChildByName("cloud_1_2"));
	this->scheduleUpdate();
	return true;
}

bool GameScene::animationYellowScene()
{
	rootNode = CSLoader::createNode("scenes/Yellow.csb");
	this->addChild(rootNode);
	Sprite* leaf_1_1 = static_cast<Sprite*>(rootNode->getChildByName("leaf_1_1"));
	leaf_1_1->setTag(TAG_LEAF1);
	_vec.pushBack(leaf_1_1);
	AALeaf->spriteLeaf = leaf_1_1;
	AALeaf->playLeafAnim();
	Sprite* leaf_1_2 = dynamic_cast<Sprite*>(rootNode->getChildByName("leaf_1_2"));
	leaf_1_2->setTag(TAG_LEAF2);
	_vec.pushBack(leaf_1_2);
	Sprite* leaf_1_3 = dynamic_cast<Sprite*>(rootNode->getChildByName("leaf_1_3"));
	leaf_1_3->setTag(TAG_LEAF1);
	_vec.pushBack(leaf_1_3);
	Sprite* leaf_2_1 = dynamic_cast<Sprite*>(rootNode->getChildByName("leaf_2_1"));
	leaf_2_1->setTag(TAG_LEAF2);
	_vec.pushBack(leaf_2_1);
	Sprite* leaf_2_2 = dynamic_cast<Sprite*>(rootNode->getChildByName("leaf_2_2"));
	leaf_2_2->setTag(TAG_LEAF1);
	_vec.pushBack(leaf_2_2);
	Sprite* leaf_2_3 = dynamic_cast<Sprite*>(rootNode->getChildByName("leaf_2_3"));
	leaf_2_3->setTag(TAG_LEAF2);
	_vec.pushBack(leaf_2_3);
	Sprite* leaf_2_4 = dynamic_cast<Sprite*>(rootNode->getChildByName("leaf_2_4"));
	leaf_2_4->setTag(TAG_LEAF1);
	_vec.pushBack(leaf_2_4);
	Sprite* leaf_3_1 = dynamic_cast<Sprite*>(rootNode->getChildByName("leaf_3_1"));
	_vec.pushBack(leaf_3_1);
	Sprite* leaf_3_2 = dynamic_cast<Sprite*>(rootNode->getChildByName("leaf_3_2"));
	leaf_3_2->setTag(TAG_LEAF1);
	_vec.pushBack(leaf_3_2);
	Sprite* leaf_3_3 = dynamic_cast<Sprite*>(rootNode->getChildByName("leaf_3_3"));
	leaf_3_3->setTag(TAG_LEAF2);
	_vec.pushBack(leaf_3_3);
	this->schedule(schedule_selector(GameScene::MoveAction), 0.5f);
	sceneType == SCENE_YELLOW;
	return true;
}

bool GameScene::animationGreenScene()
{
	rootNode = CSLoader::createNode("scenes/Green-scene.csb");
	this->addChild(rootNode);
	tree_1 = static_cast<Sprite*>(rootNode->getChildByName("tree_1"));
	tree_2 = static_cast<Sprite*>(rootNode->getChildByName("tree_2"));
	tree_3 = static_cast<Sprite*>(rootNode->getChildByName("tree_3"));
	tree_4 = static_cast<Sprite*>(rootNode->getChildByName("tree_4"));
	auto rotateToRight = RotateBy::create(0.7, 60);
	auto rotateToLeft = RotateBy::create(0.7, -60);
	auto sqLR = Sequence::create(rotateToRight, rotateToLeft, NULL);
	auto RsqLR = RepeatForever::create(sqLR);
	tree_1->runAction(RsqLR);
	auto rotateToRight2 = RotateBy::create(0.7, 60);
	auto rotateToLeft2 = RotateBy::create(0.7, -60);
	auto sqLR2 = Sequence::create(rotateToRight2, rotateToLeft2, NULL);
	auto RsqLR2 = RepeatForever::create(sqLR2);
	tree_2->runAction(RsqLR2);
	auto rotateToRight3 = RotateBy::create(0.7, 60);
	auto rotateToLeft3 = RotateBy::create(0.7, -60);
	auto sqLR3 = Sequence::create(rotateToRight3, rotateToLeft3, NULL);
	auto RsqLR3 = RepeatForever::create(sqLR3);
	tree_3->runAction(RsqLR3);
	auto rotateToRight4 = RotateBy::create(0.7, 60);
	auto rotateToLeft4 = RotateBy::create(0.7, -60);
	auto sqLR4 = Sequence::create(rotateToRight4, rotateToLeft4, NULL);
	auto RsqLR4 = RepeatForever::create(sqLR4);
	tree_4->runAction(RsqLR4);
	sceneType = SCENE_GREEN;
	this->schedule(schedule_selector(GameScene::MoveAction), 0.4f);
	return true;
}

bool GameScene::animationPurpleScene()
{
	rootNode = CSLoader::createNode("scenes/Blue-scene.csb");
	this->addChild(rootNode);
	cloud_1 = static_cast<Sprite*>(rootNode->getChildByName("cloud_1"));
	cloud_2 = static_cast<Sprite*>(rootNode->getChildByName("cloud_2"));
	cloud_3 = static_cast<Sprite*>(rootNode->getChildByName("cloud_3"));
	Sprite* light = static_cast<Sprite*>(rootNode->getChildByName("light"));
	auto rotateAction = RotateBy::create(5.0f, 360);
	auto rotateAll = RepeatForever::create(rotateAction);
	sceneType = SCENE_PURPLE;
	light->runAction(rotateAll);
	this->scheduleUpdate();
	return true;
}

bool GameScene::animationChristmasScene()
{
	rootNode = CSLoader::createNode("scenes/Chrismas-scene.csb");
	this->addChild(rootNode);
	deer = dynamic_cast<Sprite*>(rootNode->getChildByName("deer"));
	auto moveDeer = MoveBy::create(9.0f, Vec2(visibleSize.width*1.3, 0));
	auto resetPosition = CallFunc::create([&]
	{
		deer->setPosition(Vec2(-visibleSize.width*0.08, visibleSize.height*0.8));
	});
	auto delay = DelayTime::create(12);
	auto sequence = Sequence::create(moveDeer, resetPosition, delay, NULL);
	auto deerAll = RepeatForever::create(sequence);
	deer->runAction(deerAll);
	auto meteor = ParticleMeteor::create();
	meteor->setScale(0.3f);
	meteor->setPosition(Vec2(-visibleSize.width*0.17, visibleSize.height*0.72));
	this->addChild(meteor);
	auto movePac = MoveBy::create(9.0f, Vec2(visibleSize.width*1.3, 0));
	auto deletePac = CallFunc::create([&]{
		RemoveSelf(meteor);
	});
	auto PacAll = Sequence::create(movePac, deletePac, NULL);
	meteor->runAction(PacAll);
	sceneType = SCENE_CHRISTMAS;
	this->schedule(schedule_selector(GameScene::MoveAction), 21.0f);

	snow1 = dynamic_cast<Sprite*>(rootNode->getChildByName("snow1"));
	snow2 = dynamic_cast<Sprite*>(rootNode->getChildByName("snow2"));
	snow3 = dynamic_cast<Sprite*>(rootNode->getChildByName("snow3"));
	snow4 = dynamic_cast<Sprite*>(rootNode->getChildByName("snow4"));
	this->schedule(schedule_selector(GameScene::SnowDrop), 5.0f);
	return true;
}

bool GameScene::animationLoadScene()
{
	return true;
}

void GameScene::update(float dt)
{
	if (sceneType == SCENE_PURPLE)
	{
		float cloud_1_posX = (float)cloud_1->getPositionX();
		float cloudMoveSpeed_1 = 0.5f;
		cloud_1_posX -= cloudMoveSpeed_1;

		float cloud_2_posX = (float)cloud_2->getPositionX();
		float cloudMoveSpeed_2 = 0.3f;
		cloud_2_posX -= cloudMoveSpeed_2;

		float cloud_3_posX = (float)cloud_3->getPositionX();
		float cloudMoveSpeed_3 = 0.4f;
		cloud_3_posX -= cloudMoveSpeed_3;
		if (cloud_1_posX < 0)
		{
			cloud_1_posX = visibleSize.width;
		}
		if (cloud_2_posX < 0)
		{
			cloud_2_posX = visibleSize.width;
		}
		if (cloud_3_posX < 0)
		{
			cloud_3_posX = visibleSize.width;
		}
		cloud_1->setPositionX(cloud_1_posX);
		cloud_2->setPositionX(cloud_2_posX);
		cloud_3->setPositionX(cloud_3_posX);
	}
	else if (sceneType = SCENE_RED)
	{
		float cloud_1_posX = (float)cloud_1->getPositionX();
		float cloudMoveSpeed_1 = 0.5;
		cloud_1_posX -= cloudMoveSpeed_1;

		float cloud_2_posX = (float)cloud_2->getPositionX();
		float cloudMoveSpeed_2 = 0.3f;
		cloud_2_posX -= cloudMoveSpeed_2;
		if (cloud_1_posX < 0)
		{
			cloud_1_posX = visibleSize.width;
		}
		if (cloud_2_posX < 0)
		{
			cloud_2_posX = visibleSize.width;
		}
		cloud_1->setPositionX(cloud_1_posX);
		cloud_2->setPositionX(cloud_2_posX);
	}

}

//code for test by Young
void GameScene::SpriteMoveUpdate(float dt)
{
	m_count = m_count + 1.0f / 60;
	//if (m_count+ 2.0f > timeArray[m_array_index] && m_array_index < FRESHHAND_ARRAY_LENGTH)  //新手
    if (m_count+ time_offset > timeArray[m_array_index] && m_array_index < SIMPLE_ARRAY_LENGTH)
	{
		DropObject* test_sprite = nullptr;
		if (m_array_index % 2 == 1)
		{
			//test_sprite = DropObject::createObject(TYPE_ONE);
			//test_sprite->setPosition(Vec2(left_circle_center.x, visibleSize.height + test_sprite->getContentSize().height / 2));
            //auto seq = JsonMoveHandler::GetInstance()->GenerateAction();
			//test_sprite->runAction(seq);
            test_sprite = DropObject::createObject(TYPE_ONE);
            test_sprite->setPosition(Vec2(left_circle_center.x, visibleSize.height + test_sprite->getContentSize().height / 2));
            test_sprite->Move(left_circle_center, left_circle_center - Vec2(0, 2 * left_circle_radius), 0.8f, 0.2f, LINE);		}
		else
		{
			test_sprite = DropObject::createObject(TYPE_TWO);
			test_sprite->setPosition(Vec2(right_circle_center.x, visibleSize.height + test_sprite->getContentSize().height / 2));
			test_sprite->Move(right_circle_center, right_circle_center - Vec2(0, 2 * right_circle_radius), 0.8f, 0.2f, LINE);
		}
		this->addChild(test_sprite);
		m_sprite_vec.pushBack(test_sprite);
		m_array_index++;
	}
}

bool GameScene::onTouchBegan(Touch* tTouch, Event* eEvent)
{
	return true;
}

void GameScene::onTouchMoved(Touch* tTouch, Event* eEvent)
{

}

void GameScene::onTouchEnded(Touch* tTouch, Event* eEvent)
{
	m_collison_detection_switch = true;
}

void GameScene::CollisonDetectionUpdate(float dt)
{
	if (m_acceleration_switch == true || m_collison_detection_switch == true)
	{
		if (m_acceleration_switch)
		{
			m_acceleration_switch = false;
		}
		else
		{
			m_collison_detection_switch = false;
		}
		if (m_sprite_vec.empty() == false)
		{
			if (m_sprite_vec.front()->getPositionX() < 480)
			{
				HitType left_type = m_sprite_vec.front()->JudgeHit(left_circle_radius, left_circle_center);
				ShowHitFeedback(left_type, m_sprite_vec.front()->getPosition());
			}
			else if (m_sprite_vec.front()->getPositionX() > 480)
			{
				HitType right_type = m_sprite_vec.front()->JudgeHit(right_circle_radius, right_circle_center);
				ShowHitFeedback(right_type, m_sprite_vec.front()->getPosition());
			}
			m_sprite_vec.front()->removeFromParentAndCleanup(true);
			m_sprite_vec.eraseObject(m_sprite_vec.front());
		}
	}
}

void GameScene::ShowHitFeedback(HitType type, Vec2 position)
{
	cocos2d::Label* label = nullptr;
	if (type == MISS)
	{
		label = cocos2d::Label::createWithBMFont("fonts/futura-48.fnt", "MISS");
	}
	else if (type == PERFECT)
	{
		label = cocos2d::Label::createWithBMFont("fonts/futura-48.fnt", "PERFECT");
	}
	else if (type == GOOD)
	{
		label = cocos2d::Label::createWithBMFont("fonts/futura-48.fnt", "GOOD");
	}
	label->setPosition(position);
	auto delay = DelayTime::create(0.5);
	auto sequence = Sequence::create(delay, RemoveSelf::create(), nullptr);
	label->runAction(sequence);
	this->addChild(label);
}

void GameScene::DestinationRemoveUpdate(float dt)
{
	if (m_sprite_vec.empty() == false)
	{
		if (m_sprite_vec.front()->getPositionX() < 480)
		{
			if (m_sprite_vec.front()->getPositionY() < (left_circle_center.y - 2*left_circle_radius+1))
				//&& m_sprite_vec.front()->JudgeHit(left_circle_radius, left_circle_center) == GOOD)
			{
				ShowHitFeedback(MISS, m_sprite_vec.front()->getPosition());
				m_sprite_vec.front()->removeFromParentAndCleanup(true);
				m_sprite_vec.eraseObject(m_sprite_vec.front());
			}
		}
		else if (m_sprite_vec.front()->getPositionX() > 480)
		{
			if (m_sprite_vec.front()->getPositionY() < (right_circle_center.y - 2*right_circle_radius+1))
				//&& m_sprite_vec.front()->JudgeHit(right_circle_radius, right_circle_center) == GOOD)
			{
				ShowHitFeedback(MISS, m_sprite_vec.front()->getPosition());
				m_sprite_vec.front()->removeFromParentAndCleanup(true);
				m_sprite_vec.eraseObject(m_sprite_vec.front());
			}
		}
	}
}

void GameScene::MoveAction(float dt)
{
	if (sceneType == SCENE_YELLOW)
	{
		//srand((UINT)GetCurrentTime());
		int iRand = (rand() % 10);
		Sprite* _leaf = _vec.at(iRand);
		_leaf->setTag(TAG_LEAF2);
		AALeaf->spriteLeaf = _leaf;
		AALeaf->playLeafAnim();
	}
	else if (sceneType == SCENE_GREEN)
	{
		srand((unsigned int)time(0)); //设置随机种子
		dropPosition = random(0.f, visibleSize.width);
		drop = Sprite::create("res/Green_Scene/drop_1.png");
		drop->setPosition(Vec2(dropPosition, visibleSize.height*0.8f));
		this->addChild(drop, 3);
		auto _drop = MoveBy::create(3.0f, Vec2(0, -visibleSize.height));
		auto easeIn = EaseIn::create(_drop, 2.0f);
		auto sDelete = CallFunc::create([&]
		{
			RemoveSelf(_drop);
		});
		auto dropAll = Sequence::create(easeIn, sDelete, NULL);
		drop->runAction(dropAll);
	}
	else if (sceneType == SCENE_CHRISTMAS)
	{
		auto meteor = ParticleMeteor::create();
		meteor->setScale(0.3f);
		meteor->setPosition(Vec2(-visibleSize.width*0.17, visibleSize.height*0.72));
		this->addChild(meteor);
		auto movePac = MoveBy::create(9.0f, Vec2(visibleSize.width*1.3, 0));
		auto deletePac = CallFunc::create([&]{
			this->removeChild(meteor, true);//在这里并没有销毁，表示疑问？
		});
		auto PacAll = Sequence::create(movePac, deletePac, NULL);
		meteor->runAction(PacAll);
	}
}

void GameScene::SnowDrop(float dt)
{
	auto newsnow = Sprite::create("res/Chrismas_Scene/snow1.png");
	newsnow->setPosition(Vec2(dropPosition, visibleSize.height + newsnow->getContentSize().height));
	this->addChild(newsnow);
	srand((unsigned int)time(0)); //设置随机种子
	dropPosition = random(0.f, visibleSize.width);
	auto _drop = MoveBy::create(10.0f, Vec2(0, -visibleSize.height));
	auto _rotateSnow = RotateBy::create(6.0f, 360);
	auto _rotateAll = Repeat::create(_rotateSnow, 30.0f);
	auto deleteSnow = CallFunc::create([&]{
		//this->removeChild(newsnow, true);
		RemoveSelf(newsnow);
	});
	auto _snowT = Spawn::create(_rotateAll, _drop, NULL);
	auto _snowAll = Sequence::create(_snowT, deleteSnow, NULL);
	newsnow->runAction(_snowAll);
}

void GameScene::menuCloseCallback(cocos2d::Ref* pSender)
{
    Audio::getInstance()->stopEffects();
    Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5, Home::createScene()));
}

//code for test by Young


