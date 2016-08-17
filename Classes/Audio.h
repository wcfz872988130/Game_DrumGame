#pragma once
#include <cocos2d.h>
#include <SimpleAudioEngine.h>
/**
 * Audio : 单例
 * Usage : Audio::getInstance()->playBackground("bg.wav");
 */
class Audio
{
public:
	static Audio * getInstance()
	{
		static Audio instance;
		return &instance;
	}

	void playBackground(const char* filename);

	void playEffect(const char* filename);

	void stopBackground(bool releaseData = false);

	void stopEffects();

	void stopEffect(unsigned int soundID);
};
