#pragma once

#ifndef			PopUp
#define			PopUp(_message)			MessageBox(NULL, _message, L"System Message", MB_OK)
#endif


#ifndef			errorHandle
#define			errorHandle(_message) catch(...){MessageBox(NULL, _message, L"Error Message", MB_OK);}
#endif


#ifdef	ENGINE_EXPORTS
#define ENGINE_DLL		_declspec(dllexport)
#else
#define ENGINE_DLL		_declspec(dllimport)
#endif


#define PI 3.14159265357989f



#ifndef abstract
#define abstract =0
#endif






