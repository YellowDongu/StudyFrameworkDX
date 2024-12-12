#pragma once
#ifndef Engine_Define_h__
#define Engine_Define_h__

#include <windows.h>
#include <string>
#include <vector>
#include <list>
#include <functional>
#include <fstream>
#include <map>
#include <thread>
#include <memory>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")




#pragma warning(disable : 4251)


#include "Engine_Define.h"
#include "Engine_TypeDef.h"
#include "Engine_Struct.h"




#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif

#endif