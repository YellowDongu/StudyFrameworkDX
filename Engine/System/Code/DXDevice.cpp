#include "Engine_base.h"
#include "DXDevice.h"

using namespace Engine;

DXDevice::DXDevice(void) : instance(nullptr), hWnd(nullptr), d3d(nullptr), d3dDevice(nullptr)
{
}

DXDevice::~DXDevice(void)
{
}


HRESULT DXDevice::initalizeD3D(void)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);

    if (!d3d)
        return E_FAIL;

    D3DCAPS9 deviceCaps;
    ZeroMemory(&deviceCaps, sizeof(deviceCaps));

    if (FAILED(d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &deviceCaps)))
        return E_FAIL;

    DWORD vertexProcess(0);

    if (deviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
    {
        vertexProcess |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
    }
    else vertexProcess |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

    D3DPRESENT_PARAMETERS d3dpp = {};
    ZeroMemory(&d3dpp, sizeof(d3dpp));

    d3dpp.BackBufferWidth = 800;
    d3dpp.BackBufferHeight = 600;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
    d3dpp.MultiSampleQuality = 0;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;
    d3dpp.Windowed = TRUE;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
    //d3dpp.Flags;

    d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vertexProcess, &d3dpp, &d3dDevice)))
        return E_FAIL;

    d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    //d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    d3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    d3dDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_ARGB(255, 0, 255, 0));

    return S_OK;
}

void Engine::DXDevice::resetDevice(void)
{
    D3DPRESENT_PARAMETERS d3dpp = {};
    ZeroMemory(&d3dpp, sizeof(d3dpp));

    d3dpp.BackBufferWidth = 800;
    d3dpp.BackBufferHeight = 600;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
    d3dpp.MultiSampleQuality = 0;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;
    d3dpp.Windowed = TRUE;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
    //d3dpp.Flags;
    d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    if (d3dDevice->Reset(&d3dpp) == D3D_OK)
        return;

    release();
    if (FAILED(initalizeD3D()))
    {
        PostQuitMessage(0);
    }
}

void DXDevice::render(std::function<void(LPDIRECT3DDEVICE9)> renderFunction)
{
    d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 255, 0), 1.0f, 0);
    d3dDevice->BeginScene();

    renderFunction(d3dDevice);

    d3dDevice->EndScene();
    if (d3dDevice->Present(NULL, NULL, hWnd, NULL) == D3DERR_DEVICEREMOVED)
        resetDevice();

}

void DXDevice::release(void)
{
    if (d3dDevice)
        d3dDevice->Release();
    if (d3d)
        d3d->Release();
}

std::shared_ptr<DXDevice> Engine::DXDevice::instantiate(HINSTANCE _instance, HWND _hWnd)
{
    std::shared_ptr<DXDevice> newDevice = std::make_shared<DXDevice>();
    newDevice->initalize(_instance, _hWnd);

    return newDevice;
}

HRESULT DXDevice::initalize(HINSTANCE _instance, HWND _hWnd)
{
    instance = _instance;
    hWnd = _hWnd;

    if (FAILED(initalizeD3D()))
        return E_FAIL;

    return S_OK;
}



