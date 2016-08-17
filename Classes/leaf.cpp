#include"leaf.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

void Leaf::resetLeafPos()
{
	int iTag = int(spriteLeaf->getTag());//获得被重置叶片的标签
	int iZoder = int(spriteLeaf->getZOrder());//获取被重置叶片的z轴值
	//spriteLeaf->setVisible(false);
	//sender->removeFromParentAndCleanup(true);//清除已经落到底点的叶子

	//char sImg[15] = "img_yezi_1.png";
	//_snprintf(sImg, sizeof(sImg), "img_yezi_%d.png", iTag % 100);

	cocos2d::Vec2 pos;
	float fAngle;
	//随机生成叶子的起始位置
	//srand((UINT)GetCurrentTime());
	int iRand = (rand() % 200);
	if (iTag == TAG_LEAF1)
	{
		pos = cocos2d::Vec2(iRand, 600);
		fAngle = 30;
	}
	else
	{
		pos = cocos2d::Vec2(iRand, 570);
		fAngle = 50;
	}
	//重新生成新的叶片，在起点处释放
	//spriteLeaf->setScale(0.5);
	spriteLeaf->setAnchorPoint(cocos2d::Vec2(0.5, 3));
	spriteLeaf->setRotation(fAngle);
	spriteLeaf->setPosition(pos);

	//this->addChild(sender, iZoder, iTag);
	this->playLeafAnim();//重置后的树叶再次执行飘落动作
}

void Leaf::playLeafAnim()
{
	cocos2d::Vec2 spos = spriteLeaf->getPosition();
	int iTag = spriteLeaf->getTag();
	float time, roTime;
	float fAngle1, fAngle2;
	if (iTag == TAG_LEAF1)
	{
		time = 10;//叶子下落的时间
		roTime = 2.5;//叶子单向摆动一次时间
		fAngle1 = -80;//叶子逆时针摆动角度
		fAngle2 = 80;//顺时针摆动角度
	}
	else
	{
		time = 14;
		roTime = 3.2;
		fAngle1 = -100;
		fAngle2 = 100;
	}
	//随机生成叶子横向偏移值
	//srand((UINT)GetCurrentTime());
	int iRandPos = rand() % 250;
	//叶子所运动到的位置
	cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(time, cocos2d::Vec2(cocos2d::Director::sharedDirector()->getWinSize().width - iRandPos, 10));
	//cocos2d::CallFuncN* actDone = cocos2d::CallFuncN::create(CC_CALLBACK_0(Leaf::resetLeafPos, this));
	auto putdown = cocos2d::Sequence::create(moveTo,NULL);
	//叶子旋转动作
	cocos2d::RotateBy *rotaBy1 = cocos2d::RotateBy::create(roTime, fAngle1);
	cocos2d::RotateBy *rotaBy2 = cocos2d::RotateBy::create(roTime, fAngle2);

	//叶子翻转动作
	spriteLeaf->setVertexZ(60);//设置深度抬高60，避免出现使用CCOrbitCamera实现空间翻转时产生错位和遮挡等问题
	//CCDirector::sharedDirector()->setDepthTest(false);
	//关闭深度测试同样可以避免上述问题，不过，推荐使用深度设置setVertexZ来正确解决，因为有时你可能需要遮挡的效果，关闭深度测试后将造成遮挡效果的缺失
	cocos2d::OrbitCamera * orbit = cocos2d::OrbitCamera::create(8, 1, 0, 0, 360, 45, 0);
	//让树叶精灵始终执行三维翻转的动作
	cocos2d::Repeat *fz3d = cocos2d::Repeat::create(orbit, -1);//无限循环执行叶片翻转的动作
	//CCRepeatForever *fz3d = CCRepeatForever::actionWithAction(orbit);
	//由于下面使用CCSpawn同时执行动作，所以不可以使用无限次数类型的动作，而因使用有线次数循环CCRepeat将循环次数设置为-1

	//用CCEaseInOut包装落叶摆动的动作，让树叶的进入、出现更自然（淡入淡出效果）
	auto ease1 = cocos2d::EaseInOut::create(rotaBy1, 3);
	auto ease2 = cocos2d::EaseInOut::create(rotaBy2, 3);
	//摆动动作合成
	auto seq2 = cocos2d::Sequence::create(ease1, ease2, NULL);//依次执行顺时针、逆时针摆动
	auto baidong = cocos2d::Repeat::create(seq2, -1);//摆动合成
	auto mov = cocos2d::CallFunc::create([&]{
		spriteLeaf->setPosition(spos);
	});
	//动作执行->同时执行所有动作
	auto m_all = cocos2d::Spawn::create(putdown, baidong, fz3d, NULL);
	spriteLeaf->runAction(cocos2d::Sequence::create(m_all,mov, NULL));
	//_spriteLeaf = spriteLeaf;
}

