#pragma once

#ifndef PCH_H
#define PCH_H

#include "framework.h"
#include "Engine.h"


#include "base.hpp"
#pragma comment (lib, "JusinSREngineSystem.lib")
#pragma comment (lib, "JusinSREngineUtility.lib")

// 메모리 누수 검사
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 
#endif
#endif




#endif //PCH_H


// global area

extern HWND windowHandle;
extern HINSTANCE instance;

extern std::map<std::wstring, Engine::GameObject> nonDestroyObject;
extern std::map<std::wstring, Engine::Component> nonDestroyComponent;
