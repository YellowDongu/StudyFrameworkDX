#include <Engine_base.h>
#include "InputManager.h"

using namespace Engine;

InputManager* InputManager::create(const HINSTANCE& hInstance, const HWND& _hwnd)
{
	InputManager* input = new InputManager();
	input->hwnd = _hwnd;
	input->states.resize(KEY_TYPE_COUNT, KeyState::None);
	input->mouseStates.resize((int)MouseKey::END, KeyState::None);

	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&input->dInput, NULL)))
	{
		delete input;
		return nullptr;
	}

	// 키보드 장치 생성
	if (FAILED(input->dInput->CreateDevice(GUID_SysKeyboard, &input->dInputDevice, NULL)))
	{
		delete input;
		return nullptr;
	}

	// 마우스 장치 생성
	if (FAILED(input->dInput->CreateDevice(GUID_SysMouse, &input->dMouseDevice, NULL)))
	{
		delete input;
		return nullptr;
	}

	// 장치에 대한 객체를 설정
	if (FAILED(input->dInputDevice->SetCooperativeLevel(_hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		delete input;
		return nullptr;
	}

	// 장치에 대한 객체를 설정
	if (FAILED(input->dMouseDevice->SetCooperativeLevel(_hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		delete input;
		return nullptr;
	}

	// 키보드 데이터 포맷 설정
	if (FAILED(input->dInputDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		delete input;
		return nullptr;
	}

	// 키보드 데이터 포맷 설정
	if (FAILED(input->dMouseDevice->SetDataFormat(&c_dfDIMouse)))
	{
		delete input;
		return nullptr;
	}

	return input;
}

void InputManager::update(void)
{

	// 프레임마다 키를 모두 스캔해서 갱신
	BYTE asciiKeys[KEY_TYPE_COUNT] = {};

	HRESULT hr = dInputDevice->GetDeviceState(sizeof(asciiKeys), (LPVOID)&asciiKeys);
	if (FAILED(hr))
	{
		if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
		{
			if (FAILED(dInputDevice->Acquire()))
				return;
		}
		else return;
	}

	for (UINT32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		if (asciiKeys[key] & 0x80)
		{
			KeyState& state = states[key];
			if (state == KeyState::Press) { continue; }
			else if (state == KeyState::Down)
			{
				state = KeyState::Press;
				continue;
			}
			else
			{
				state = KeyState::Down;
				continue;
			}
			if (state == KeyState::END) { state = KeyState::None; }
		}
		else
		{
			KeyState& state = states[key];
			if (state == KeyState::None) { continue; }
			if (state == KeyState::Up)
			{
				state = KeyState::None;
				continue;
			}
			else
			{
				state = KeyState::Up;
				continue;
			}
			if (state == KeyState::END) { state = KeyState::None; }
		}
	}

	hr = dMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState);
	if (FAILED(hr))
	{
		if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
		{
			if (FAILED(dMouseDevice->Acquire()))
				return;
		}
		else return;
	}

	mouseMove.x = mouseState.lX;
	mouseMove.y = mouseState.lY;
	mouseWheel = mouseState.lZ;

	for (int i = (int)MouseKey::LButton; i < (int)MouseKey::END; i++)
	{
		if (mouseState.rgbButtons[i] & 0x80)
		{
			KeyState& state = mouseStates[i];
			if (state == KeyState::Press) { continue; }
			else if (state == KeyState::Down)
			{
				state = KeyState::Press;
				continue;
			}
			else
			{
				state = KeyState::Down;
				continue;
			}
			if (state == KeyState::END) { state = KeyState::None; }
		}
		else
		{
			KeyState& state = mouseStates[i];
			if (state == KeyState::None) { continue; }
			if (state == KeyState::Up)
			{
				state = KeyState::None;
				continue;
			}
			else
			{
				state = KeyState::Up;
				continue;
			}
			if (state == KeyState::END) { state = KeyState::None; }
		}
	}


	POINT previousPosition = mousePos;
	if (fixedMouse)
	{
		//RECT windowRect = {};
		//GetWindowRect(hwnd, &windowRect);
		SetCursorPos(400, 300);
	}
	GetCursorPos(&mousePos);
	ScreenToClient(hwnd, &mousePos);
	//mouseMove = { mousePos.x - previousPosition.x, mousePos.y - previousPosition.y };
	//
	//if (mouseMove.x != 0 || mouseMove.y != 0)
	//	int alarm = 0;


}

void InputManager::release(void)
{
	if (dInputDevice)
	{
		dInputDevice->Unacquire();
		dInputDevice->Release();
	}
	if (dInput)
	{
		dInput->Release();
	}
}

void InputManager::fixingMouse(bool value)
{
	if (fixedMouse == value)
		return;

	fixedMouse = value;
	ShowCursor(value);
}

void InputManager::raycastViewSpace(const LPDIRECT3DDEVICE9& device, Vector3& rayDirection)
{
	D3DVIEWPORT9 viewport;
	ZeroMemory(&viewport, sizeof(D3DVIEWPORT9));
	if (FAILED(device->GetViewport(&viewport)))
		return;

	D3DXMATRIXA16 projectionMatrix, projectionMatrixInverse;
	ZeroMemory(&projectionMatrix, sizeof(D3DXMATRIXA16));
	if (FAILED(device->GetTransform(D3DTS_PROJECTION, &projectionMatrix)))
		return;

	D3DXMatrixInverse(&projectionMatrixInverse, 0, &projectionMatrix);

	rayDirection.x = (( 2.0f * mousePos.x) / viewport.Width  - 1.0f) * projectionMatrixInverse._11;
	rayDirection.y = ((-2.0f * mousePos.y) / viewport.Height + 1.0f) * projectionMatrixInverse._22;
	rayDirection.z = 1.0f;
	D3DXVec3Normalize(&rayDirection, &rayDirection);
}

void InputManager::raycastWorldSpace(const LPDIRECT3DDEVICE9& device, Vector3& rayOrigin, Vector3& rayDirection)
{
	raycastViewSpace(device, rayDirection);
	D3DXMATRIXA16 viewMatrix, viewMatrixInverse;

	if (FAILED(device->GetTransform(D3DTS_VIEW, &viewMatrix)))
		return;

	D3DXMatrixInverse(&viewMatrixInverse, 0, &viewMatrix);

	rayOrigin = { viewMatrixInverse._41, viewMatrixInverse._42, viewMatrixInverse._43 };
	D3DXVec3TransformNormal(&rayDirection, &rayDirection, &viewMatrixInverse);
	D3DXVec3Normalize(&rayDirection, &rayDirection);
}



//void raycastViewSpace(POINT mousePos, const LPDIRECT3DDEVICE9& device, Vector3& rayDirection)
//{
//	D3DVIEWPORT9 viewport;
//	if(FAILED(device->GetViewport(&viewport)))
//		return;
//	D3DXMATRIXA16 projectionMatrix;
//	if (FAILED(device->GetTransform(D3DTS_PROJECTION, &projectionMatrix)))
//		return;
//
//	rayDirection.x = (( 2.0f * mousePos.x) / viewport.Width - 1.0f) / projectionMatrix._11;
//	rayDirection.y = ((-2.0f * mousePos.y) / viewport.Height+ 1.0f) / projectionMatrix._22;
//	rayDirection.z = 1.0f;
//}
//
//void raycastWorldSpace(const POINT mousePos, const LPDIRECT3DDEVICE9& device, Vector3& rayOrigin, Vector3& rayDirection)
//{
//	raycastViewSpace(mousePos, device, rayDirection);
//	D3DXMATRIXA16 viewMatrix, viewMatrixInverse;
//
//	if (FAILED(device->GetTransform(D3DTS_VIEW, &viewMatrix)))
//		return;
//
//	D3DXMatrixInverse(&viewMatrixInverse, 0, &viewMatrix);
//
//	D3DXVec3TransformCoord(&rayOrigin, &rayOrigin, &viewMatrixInverse);
//	D3DXVec3TransformNormal(&rayDirection, &rayDirection, &viewMatrixInverse);
//	D3DXVec3Normalize(&rayDirection, &rayDirection);
//}
