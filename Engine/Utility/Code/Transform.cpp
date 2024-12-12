#include "Engine_base.h"
#include"Transform.h"

using namespace Engine;


Transform::Transform(void) : scale(1.0f, 1.0f, 1.0f), rotation(0.0f, 0.0f, 0.0f), position(0.0f, 0.0f, 0.0f),
calculateVector{}, worldMatrix()
{
}

Transform::~Transform(void)
{
}

Transform::Transform(LPDIRECT3DDEVICE9& _device) : Component(_device), scale(0.0f,0.0f,0.0f), rotation(0.0f,0.0f,0.0f), position(0.0f,0.0f,0.0f),
calculateVector{}, worldMatrix()
{
	initializeValue();
}

Transform::Transform(const Transform& origin) : Component(origin), scale(origin.scale), rotation(origin.rotation), position(origin.position),
calculateVector(), worldMatrix(origin.worldMatrix)
{
	for (int i = 0; i < 3; i++)
		calculateVector[i] = origin.calculateVector[i];
}

void Transform::update(void)
{
	initializeValue();

	// 크기 변환
	for (int i = 0; i < 3; ++i)
		calculateVector[i] *= *(((float*)&scale) + i);
	
	// 회전 변환
	Matrix rotationMatix;
	D3DXMatrixRotationYawPitchRoll(&rotationMatix, rotation.y, rotation.x, rotation.z);
	
	for (int i = 0; i < 3; ++i)
		D3DXVec3TransformNormal(&calculateVector[i], &calculateVector[i], &rotationMatix);
	
	for (int i = 0; i < 3; ++i)
	{
		memcpy(&worldMatrix.m[i][0], &calculateVector[i], sizeof(Vector3));
		worldMatrix.m[3][i] = *(((float*)&position) + i);
	}
}

void Transform::start(void)
{
	initializeValue();
}

void Transform::release(void)
{
}

Transform* Transform::create(LPDIRECT3DDEVICE9& _device)
{
	Transform* newComponent = new Transform(_device);
	newComponent->start();

	return newComponent;
}	

Component* Transform::clone()
{
	return new Transform(*this);
}

void Engine::Transform::initializeValue(void)
{
	D3DXMatrixIdentity(&worldMatrix);

	for (int i = 0; i < 3; ++i)
		memcpy(&calculateVector[i], &worldMatrix.m[i][0], sizeof(Vector3));
}

