#pragma once
#include "..\x64\fmod.h"
#include "..\x64\fmod.hpp"
#pragma comment (lib, "..\\x64\\fmodL_vc.lib")
#include "Base.hpp"

namespace Engine
{

	class ENGINE_DLL SoundManager : public Base
	{
	public:
		SoundManager(void);
		virtual ~SoundManager(void);

		//SoundManager(const SoundManager&) = delete;
		//SoundManager& operator=(const SoundManager&) = delete;

		void initiate(void);

		void update(void);
		virtual void release(void);

		void loadSound(std::wstring path, std::wstring fileName);
		void playBGM(std::wstring soundName);
		void playNew(std::wstring soundName, FMOD::Channel*& channel);
		void stopSound(FMOD::Channel* channel);
		void stopBGM(void);
		bool checkPlaying(FMOD::Channel* channel);
		void changeVolume(FMOD::Channel* channel, float value);

		FMOD::Channel*& BGMSoundChannel(void) { return BGMChannel; }
		FMOD::Channel*& createChannel(std::wstring channelName) { channels[channelName] = nullptr; return findChannel(channelName); }
		FMOD::Channel*& findChannel(std::wstring channelName) { return (*channels.find(channelName)).second; }
		FMOD::Sound*& findSound(std::wstring soundName) { return (*sounds.find(soundName)).second; }

	private:
		FMOD::System* fmodSys;
		std::map<std::wstring, FMOD::Sound*> sounds;
		std::map<std::wstring, FMOD::Channel*> channels;
		FMOD::Channel* BGMChannel;

		std::string toString(const std::wstring& wstr)
		{
			size_t size = wstr.size() * 4 + 1;
			char* buffer = new char[size];
			size_t outSize = 0;
			wcstombs_s(&outSize, buffer, size, wstr.c_str(), size - 1);
			std::string str(buffer);
			delete[] buffer;
			return str;
		}
	};

	SoundManager* Sound = nullptr;
}
