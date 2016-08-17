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
	void resetLeafPos();//叶片位置重置函数
	void playLeafAnim();//下落过程实现函数
protected:
private:
};
#endif