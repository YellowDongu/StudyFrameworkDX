#pragma once
#include "base.hpp"

namespace Engine
{
	class ENGINE_DLL DXDevice : public Base
	{
	public:
		DXDevice(void);
		virtual ~DXDevice(void);

		std::shared_ptr<DXDevice> instantiate(HINSTANCE _instance, HWND _hWnd);
		HRESULT initalize(HINSTANCE _instance, HWND _hWnd);
		HRESULT initalizeD3D(void);
		void resetDevice(void);
		void render(std::function<void(LPDIRECT3DDEVICE9)> renderFunction);
		virtual void release(void);
		
		inline LPDIRECT3DDEVICE9 getDevice(void) { return d3dDevice; }
	private:
		HINSTANCE instance;
		HWND hWnd;
		LPDIRECT3D9 d3d;
		LPDIRECT3DDEVICE9 d3dDevice;

		D3DCOLOR backBufferColor = D3DCOLOR_ARGB(255, 0, 255, 0);
	};

}
