#include "Audio.h"

void Audio::playBackground(const char* filename)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(filename);
}

void Audio::playEffect(const char* filename)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(filename);
}

void Audio::stopBackground(bool releaseData)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(releaseData);
}

void Audio::stopEffects()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}

void Audio::stopEffect(unsigned int soundID)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundID);
}
