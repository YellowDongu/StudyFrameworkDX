#pragma once
#include "Base.hpp"
#include "Engine_base.h"
#include "DXDevice.h"
#include "IOManager.h"
#include "SoundManager.h"
#include "TimeManager.h"
#include "InputManager.h"

namespace Engine
{
	std::map<std::wstring, std::shared_ptr<Base>> managers;

	//inline std::shared_ptr<DXDevice> device()
	//{
	//	auto result = managers.find(L"device");
	//	if (result == managers.end())
	//		return nullptr;
	//
	//	return (*result).second;
	//}





	// 여기선 함수는 무조건 인라인을 붙여야됨 안붙이면 링크 오류남
	// 전역변수는 ENGINE_DLL을 붙이면 난리나는듯
	inline std::shared_ptr<DXDevice> createDevice(HINSTANCE _instance, HWND _hWnd)
	{
		std::shared_ptr<DXDevice> newDevice = std::make_shared<DXDevice>();
		if (SUCCEEDED(newDevice->initalize(_instance, _hWnd)))
		{
			return newDevice;
		}
		return nullptr;
	}

	inline std::shared_ptr<TimeManager> createTime()
	{
		std::shared_ptr<TimeManager> newTime = std::make_shared<TimeManager>();
		newTime->initiate();
		return newTime;
	}

	inline std::shared_ptr<SoundManager> createSound(HINSTANCE _instance, HWND _hWnd)
	{
		std::shared_ptr<SoundManager> newSound = std::make_shared<SoundManager>();
		newSound->initiate();
		return newSound;
	}

	inline std::shared_ptr<InputManager> createInput(HINSTANCE _instance, HWND _hWnd)
	{
		InputManager* input = InputManager::create(_instance, _hWnd);

		if (!input)
			return nullptr;

		return std::shared_ptr<InputManager>(input);
	}

	//void initialDevice(HINSTANCE _instance, HWND _hWnd)
	//{
	//	//device = std::make_unique<DXDevice>(new DXDevice());
	//	device = std::unique_ptr<DXDevice>(new DXDevice());
	//	device->initalize(_instance, _hWnd);
	//}
	//
	inline void Release_System(void)
	{
		for (auto& manager : managers)
		{
			auto instance = manager.second;
			instance->release();
			if (instance.use_count() == 1)
			{
				instance.reset();
			}
		}
		managers.clear();
	}


}

