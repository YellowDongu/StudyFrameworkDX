#include <Engine_base.h>
#include "TimeManager.h"

using namespace Engine;

void TimeManager::initiate(void)
{
	prevTime = Clock::now();
	baseFPS = 60;
	setDuration();
}

void TimeManager::update(void)
{
	TimePoint currentTime = Clock::now();
	std::chrono::duration<float> elapsedTime = currentTime - prevTime;

	deltaT = elapsedTime.count();
	prevTime = currentTime;
	frameCount++;
	frameTime += deltaT;
	if (frameTime >= 1.0f)
	{
		fps = static_cast<unsigned int>(frameCount / frameTime);

		frameTime = 0.0f;
		frameCount = 0;
	}

	frameTimer += deltaT;

	if (frameTimer >= 1.0f)
		frameTimer = 0.0f;
}

bool TimeManager::isFrameElapsed(void)
{
	if (frameTimer >= frameDuration)
	{
		frameTimer -= frameDuration;
		return true;
	}
	return false;
}
