#pragma once

/**
 * TODO : CHANGE TO XLSX READER FOR DATA READ, AND MAKE A CONFIGEN FOR DYNAMIC CONFIG
 */

#include "cocos2d.h"
#include <iostream>
USING_NS_CC;
using namespace cocos2d;

// data type for read or save
enum DataType
{
	UserName,
	GameType,
};

class DataUtils
{
public:
	static void save(DataType type, std::string data);
	static std::string read(DataType type);
};

