#include"leaf.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

void Leaf::resetLeafPos()
{
	int iTag = int(spriteLeaf->getTag());//��ñ�����ҶƬ�ı�ǩ
	int iZoder = int(spriteLeaf->getZOrder());//��ȡ������ҶƬ��z��ֵ
	//spriteLeaf->setVisible(false);
	//sender->removeFromParentAndCleanup(true);//����Ѿ��䵽�׵��Ҷ��

	//char sImg[15] = "img_yezi_1.png";
	//_snprintf(sImg, sizeof(sImg), "img_yezi_%d.png", iTag % 100);

	cocos2d::Vec2 pos;
	float fAngle;
	//�������Ҷ�ӵ���ʼλ��
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
	//���������µ�ҶƬ������㴦�ͷ�
	//spriteLeaf->setScale(0.5);
	spriteLeaf->setAnchorPoint(cocos2d::Vec2(0.5, 3));
	spriteLeaf->setRotation(fAngle);
	spriteLeaf->setPosition(pos);

	//this->addChild(sender, iZoder, iTag);
	this->playLeafAnim();//���ú����Ҷ�ٴ�ִ��Ʈ�䶯��
}

void Leaf::playLeafAnim()
{
	cocos2d::Vec2 spos = spriteLeaf->getPosition();
	int iTag = spriteLeaf->getTag();
	float time, roTime;
	float fAngle1, fAngle2;
	if (iTag == TAG_LEAF1)
	{
		time = 10;//Ҷ�������ʱ��
		roTime = 2.5;//Ҷ�ӵ���ڶ�һ��ʱ��
		fAngle1 = -80;//Ҷ����ʱ��ڶ��Ƕ�
		fAngle2 = 80;//˳ʱ��ڶ��Ƕ�
	}
	else
	{
		time = 14;
		roTime = 3.2;
		fAngle1 = -100;
		fAngle2 = 100;
	}
	//�������Ҷ�Ӻ���ƫ��ֵ
	//srand((UINT)GetCurrentTime());
	int iRandPos = rand() % 250;
	//Ҷ�����˶�����λ��
	cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(time, cocos2d::Vec2(cocos2d::Director::sharedDirector()->getWinSize().width - iRandPos, 10));
	//cocos2d::CallFuncN* actDone = cocos2d::CallFuncN::create(CC_CALLBACK_0(Leaf::resetLeafPos, this));
	auto putdown = cocos2d::Sequence::create(moveTo,NULL);
	//Ҷ����ת����
	cocos2d::RotateBy *rotaBy1 = cocos2d::RotateBy::create(roTime, fAngle1);
	cocos2d::RotateBy *rotaBy2 = cocos2d::RotateBy::create(roTime, fAngle2);

	//Ҷ�ӷ�ת����
	spriteLeaf->setVertexZ(60);//�������̧��60���������ʹ��CCOrbitCameraʵ�ֿռ䷭תʱ������λ���ڵ�������
	//CCDirector::sharedDirector()->setDepthTest(false);
	//�ر���Ȳ���ͬ�����Ա����������⣬�������Ƽ�ʹ���������setVertexZ����ȷ�������Ϊ��ʱ�������Ҫ�ڵ���Ч�����ر���Ȳ��Ժ�����ڵ�Ч����ȱʧ
	cocos2d::OrbitCamera * orbit = cocos2d::OrbitCamera::create(8, 1, 0, 0, 360, 45, 0);
	//����Ҷ����ʼ��ִ����ά��ת�Ķ���
	cocos2d::Repeat *fz3d = cocos2d::Repeat::create(orbit, -1);//����ѭ��ִ��ҶƬ��ת�Ķ���
	//CCRepeatForever *fz3d = CCRepeatForever::actionWithAction(orbit);
	//��������ʹ��CCSpawnͬʱִ�ж��������Բ�����ʹ�����޴������͵Ķ���������ʹ�����ߴ���ѭ��CCRepeat��ѭ����������Ϊ-1

	//��CCEaseInOut��װ��Ҷ�ڶ��Ķ���������Ҷ�Ľ��롢���ָ���Ȼ�����뵭��Ч����
	auto ease1 = cocos2d::EaseInOut::create(rotaBy1, 3);
	auto ease2 = cocos2d::EaseInOut::create(rotaBy2, 3);
	//�ڶ������ϳ�
	auto seq2 = cocos2d::Sequence::create(ease1, ease2, NULL);//����ִ��˳ʱ�롢��ʱ��ڶ�
	auto baidong = cocos2d::Repeat::create(seq2, -1);//�ڶ��ϳ�
	auto mov = cocos2d::CallFunc::create([&]{
		spriteLeaf->setPosition(spos);
	});
	//����ִ��->ͬʱִ�����ж���
	auto m_all = cocos2d::Spawn::create(putdown, baidong, fz3d, NULL);
	spriteLeaf->runAction(cocos2d::Sequence::create(m_all,mov, NULL));
	//_spriteLeaf = spriteLeaf;
}

