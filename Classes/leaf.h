#ifndef _LEAF_H_
 #define _LEAF_H_
#include "cocos2d.h"
enum 
{
	TAG_LEAF1,
	TAG_LEAF2,
};
class Leaf
{
public:
	cocos2d::Sprite* spriteLeaf;
	void resetLeafPos();//ҶƬλ�����ú���
	void playLeafAnim();//�������ʵ�ֺ���
protected:
private:
};
#endif