#include <Engine_base.h>
#include "SoundManager.h"

using namespace Engine;

SoundManager::SoundManager(void) : sounds{}, fmodSys(nullptr), BGMChannel(nullptr)
{
}

SoundManager::~SoundManager(void)
{
	release();
}

void SoundManager::initiate(void)
{
	FMOD::System_Create(&fmodSys);
	// 최대 32채널 사용
	fmodSys->init(32, FMOD_INIT_NORMAL, 0);
	fmodSys->update();
}

void SoundManager::update(void)
{
	fmodSys->update();
}

void SoundManager::release(void)
{
	if (!fmodSys)
		return;

	if (BGMChannel)
		stopSound(BGMChannel);

	for (auto& sound : sounds)
	{
		sound.second->release();
	}
	sounds.clear();

	fmodSys->close();
	fmodSys->release();
	fmodSys = nullptr;
}

void SoundManager::loadSound(std::wstring path, std::wstring fileName)
{
	FMOD::Sound* newSound = nullptr;
	fmodSys->createSound(toString(path + fileName).c_str(), FMOD_DEFAULT, 0, &newSound);
	sounds[fileName] = newSound;
}

void SoundManager::playBGM(std::wstring soundName)
{
	if (checkPlaying(BGMChannel))
		BGMChannel->stop();

	auto sound = sounds.find(soundName);
	if (sound == sounds.end()) return;

	fmodSys->playSound(sound->second, 0, false, &BGMChannel);
	BGMChannel->setMode(FMOD_LOOP_NORMAL);
	BGMChannel->setLoopCount(-1);
}

void SoundManager::playNew(std::wstring soundName, FMOD::Channel*& channel)
{
	auto sound = sounds.find(soundName);
	if (sound == sounds.end()) return;

	fmodSys->playSound(sound->second, 0, false, &channel);
}

void SoundManager::stopSound(FMOD::Channel* channel)
{
	if (!checkPlaying(channel))
		return;
	channel->stop();
}

void SoundManager::stopBGM(void)
{
	if (!checkPlaying(BGMChannel))
		return;
	BGMChannel->stop();
}

bool SoundManager::checkPlaying(FMOD::Channel* channel)
{
	bool playing = false;
	if (channel->isPlaying(&playing) != FMOD_OK)
		return false; 
	return playing;
}

void SoundManager::changeVolume(FMOD::Channel* channel, float value)
{
	if (value > 1.0f) value = 1.0f;
	else if (value < 0.0f) value = 0.0f;
	channel->setVolume(value);
}