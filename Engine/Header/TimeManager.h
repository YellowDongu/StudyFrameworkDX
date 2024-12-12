#pragma once
#include "Base.hpp"

namespace Engine
{
	//class WTimeManager
	//{
	//	
	//	DECLARE_SINGLETON(WTimeManager);
	//
	//public:
	//	void init(void);
	//	void update(void);
	//
	//	UINT32 getFPS(void) { return fps; }
	//	float deltaTime(void) { return deltaT; }
	//private:
	//	UINT64 frequency = 0;
	//	UINT64 prevCount = 0;
	//	float deltaT = 0.0f; //이전 프레임과 현재 프레임 사이의 시간 간격 (초단위)
	//
	//	UINT32 frameCount = 0; // 현재 초 동안 프레임 수
	//	UINT32 fps = 0; //초당 프레임 수(FPS)
	//	float frameTime = 0.0f;
	//};
	//
	//#ifdef Time
	//#undef Time
	//#endif
	//#define Time GET_SINGLETON(WTimeManager)
	//
	//void WTimeManager::init(void)
	//{
	//	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));
	//	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&prevCount));
	//}
	//
	//void WTimeManager::update(void)
	//{
	//	UINT64 currentCount;
	//	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));
	//
	//	deltaT = (currentCount - prevCount) / static_cast<float>(frequency);
	//	prevCount = currentCount;
	//	frameCount++;
	//	frameTime += deltaT;
	//	if (frameTime >= 1.0f)
	//	{
	//		fps = static_cast<UINT32>(frameCount / frameTime);
	//
	//		frameTime = 0.0f;
	//		frameCount = 0;
	//	}
	//}








	class ENGINE_DLL TimeManager : public Base
	{
	public:
		TimeManager(void) {}
		virtual ~TimeManager(void) {};
		//TimeManager(const TimeManager&) = delete;
		//TimeManager& operator=(const TimeManager&) = delete;

		void initiate(void);
		void update(void);
		bool isFrameElapsed(void);
		virtual void release(void) {}

		const unsigned int& FPS(void) const { return fps; }
		const float& deltaTime(void) const { return deltaT; }

		void setTargetFPS(int value) { baseFPS = value; setDuration(); }

	private:
		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock>;
		TimePoint prevTime;

		int baseFPS = 60;
		unsigned int frameCount = 0;
		unsigned int fps = 0;

		float frameTime = 0.0f;
		float deltaT = 0.0f;
		float frameDuration = 0.0f;
		float frameTimer = 0.0f;

		void setDuration(void) { frameDuration = 1.0f / static_cast<float>(baseFPS); }
	};

}


//#ifdef Time
//#undef Time
//#endif
//#define Time Engine::TimeManager::instance()