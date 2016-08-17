#include "DataUtils.h"
#include <iostream>

#define UDefault (UserDefault::getInstance())

// user prefrence data save
void DataUtils::save(DataType type, std::string data)
{
	switch (type)
	{
	case UserName:
		{
			UDefault->setStringForKey("UserName", data);
		}
		break;
	case GameType:
		{
			UDefault->setStringForKey("GameType", data);
		}
		break;
	}
}

// user prefrence data read
std::string DataUtils::read(DataType type)
{
	switch (type)
	{
	case UserName:
		return UDefault->getStringForKey("UserName");
		break;
	case GameType:
		return UDefault->getStringForKey("GameType");
		break;
	}
	return "";
}
