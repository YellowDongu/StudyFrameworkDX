#include "Engine_base.h"
#include "Camera.h"
#include "Transform.h"

using namespace Engine;


Camera::Camera() : fov(45.0f), aspectRatio(1.0f), nearSightRange(0.1f), maximumSightRange(1000.0f),
hWnd(nullptr), transformComponent(nullptr),
windowSize(0.0f, 0.0f), directionX(0.0f, 0.0f, 0.0f), directionY(0.0f, 0.0f, 0.0f), directionZ(0.0f, 0.0f, 0.0f), up(0.0f, 0.0f, 0.0f), at(0.0f, 0.0f, 0.0f),
viewMatrix{}, projectionMatrix{}
{
}

Camera::~Camera()
{
}

Camera::Camera(LPDIRECT3DDEVICE9& _device) : GameObject(_device), fov(45.0f), aspectRatio(1.0f), nearSightRange(0.1f), maximumSightRange(1000.0f),
hWnd(nullptr), transformComponent(nullptr),
windowSize(0.0f, 0.0f), directionX(0.0f, 0.0f, 0.0f), directionY(0.0f, 0.0f, 0.0f), directionZ(0.0f, 0.0f, 0.0f), up(0.0f, 0.0f, 0.0f), at(0.0f, 0.0f, 0.0f),
viewMatrix{}, projectionMatrix{}
{
}

Camera::Camera(const Camera& other) : GameObject(other),
fov(other.fov),aspectRatio(other.aspectRatio),nearSightRange(other.nearSightRange),maximumSightRange(other.maximumSightRange),
hWnd(other.hWnd),transformComponent(other.transformComponent),
windowSize(other.windowSize), directionX(other.directionX), directionY(other.directionY), directionZ(other.directionZ),up(other.up),at(other.at),
viewMatrix(other.viewMatrix),projectionMatrix(other.projectionMatrix)
{
}





void Camera::start(void)
{
	getWindowInfo();
	fov = 45.0f;
	nearSightRange = 0.1f;
	maximumSightRange = 500.0f;
	D3DXMatrixIdentity(&viewMatrix);
	D3DXMatrixIdentity(&projectionMatrix);
	if (transformComponent)
	{
		transformComponent->release();
		delete transformComponent;
	}
	transformComponent = Transform::create(device);
	components[L"Transform"] = transformComponent;
	up = { 0.f, 1.f, 0.f };
}

void Camera::update(void)
{
	for (auto& component : components)
	{
		component.second->update();
	}

	getWindowInfo();
	directionZ = Vector3::direction(transformComponent->rotation);
	at = directionZ + transformComponent->position;
	directionX = Vector3::cross(directionZ, up);
	directionY = Vector3::cross(directionX, directionZ);

	D3DXMatrixLookAtLH(&viewMatrix, &transformComponent->position, &at, &up);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DXToRadian(fov), aspectRatio, nearSightRange, maximumSightRange);

	device->SetTransform(D3DTS_VIEW, &viewMatrix);
	device->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

}

void Camera::release(void)
{


}

GameObject* Camera::clone(void)
{
	return new Camera(*this);
}

void Camera::getWindowInfo(void)
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	windowSize.x = static_cast<float>(clientRect.right - clientRect.left);
	windowSize.y = static_cast<float>(clientRect.bottom - clientRect.top);
	aspectRatio = windowSize.x / windowSize.y;
}

Camera* Camera::create(HWND _hWnd, LPDIRECT3DDEVICE9 _device)
{
	Camera* newCamera = new Camera();
	newCamera->hWnd = _hWnd;
	newCamera->device = _device;
	newCamera->start();
	return newCamera;
}

void Camera::localRotate(Vector3 rotationRadian)
{
	//D3DXMATRIX localRotationMatrix, parentRotationMatrix;
	//D3DXMatrixRotationYawPitchRoll(&parentRotationMatrix, transformComponent->rotation.x, transformComponent->rotation.y, transformComponent->rotation.z );
	//D3DXMatrixRotationYawPitchRoll(&localRotationMatrix, rotationRadian.y, rotationRadian.x, rotationRadian.z);
	//
	//D3DXMATRIX matWorldRotation = parentRotationMatrix * localRotationMatrix;
	//
	//float degreeChange = 180.0f / D3DX_PI;
	//if (matWorldRotation._33 > 0.998f)
	//{
	//	transformComponent->rotation.y = atan2(matWorldRotation._32, matWorldRotation._22);
	//	transformComponent->rotation.x = D3DX_PI / 2;
	//	transformComponent->rotation.z = 0.0f;
	//}
	//else if (matWorldRotation._33 < -0.998f)
	//{
	//	transformComponent->rotation.y = atan2(matWorldRotation._32, matWorldRotation._22);
	//	transformComponent->rotation.x = -D3DX_PI / 2;
	//	transformComponent->rotation.z = 0.0f;
	//}
	//else
	//{
	//	transformComponent->rotation.x = asin(-matWorldRotation._33);
	//	transformComponent->rotation.y = atan2(matWorldRotation._32, matWorldRotation._11);
	//	transformComponent->rotation.z = atan2(matWorldRotation._13, matWorldRotation._23);
	//}
	//transformComponent->rotation *= degreeChange;

}
