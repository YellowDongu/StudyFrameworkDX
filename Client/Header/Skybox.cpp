#include "pch.h"
#include "Skybox.h"



Skybox::Skybox()
{
}

Skybox::~Skybox()
{
	release();
}

Skybox::Skybox(LPDIRECT3DDEVICE9& device)
{
}

Skybox::Skybox(const Skybox& other)
{
}

void Skybox::start(void)
{
	texture = Engine::Texture::create(device,L"D:\\Downloads\\10일차-높이맵 적용\\Client\\Bin\\Resource\\Texture\\SkyBox\\burger0.dds", true);
	transform = Engine::Transform::create(device);
	polygon = Engine::Polygon::create(device);



}

void Skybox::awake(void)
{
	std::vector<Engine::Texture3dVertex> vertex = {
		{{-1,-1,-1}, {-1,-1,-1}},
		{{ 1,-1,-1}, { 1,-1,-1}},
		{{ 1,-1, 1}, { 1,-1, 1}},
		{{-1,-1, 1}, {-1,-1, 1}},
		{{-1, 1,-1}, {-1, 1,-1}},
		{{ 1, 1,-1}, { 1, 1,-1}},
		{{ 1, 1, 1}, { 1, 1, 1}},
		{{-1, 1, 1}, {-1, 1, 1}}
	};

	std::vector<Engine::VertexIndex> index = {
		{0,1,2}, {0,2,3},
		{4,5,6}, {4,6,7},
		{0,3,7}, {0,7,4},
		{0,1,5}, {0,5,4},
		{1,2,6}, {1,6,5},
		{2,3,7}, {2,7,6}
	};

	polygon->createPolygon(vertex, index, true);

	transform->scale = { 100.0f,100.0f,100.0f };
}

void Skybox::update(void)
{
}

void Skybox::lateUpdate(void)
{
}

void Skybox::fixedUpdate(void)
{
}

void Skybox::render(void)
{
	//device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	transform->update();
	transform->applyWorldMatrix();
	texture->setTexture(0);
	polygon->render();

	device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void Skybox::release(void)
{
	if (isClone)
		return;


	Engine::GameObject::release();
}

Engine::GameObject* Skybox::clone(void)
{
	return nullptr;
}

Skybox* Skybox::create(LPDIRECT3DDEVICE9& _device)
{
	Skybox* newSkybox = new Skybox();
	newSkybox->device = _device;
	return newSkybox;
}