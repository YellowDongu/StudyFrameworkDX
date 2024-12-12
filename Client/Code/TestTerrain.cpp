#include "pch.h"
#include "TestTerrain.h"



TestTerrain::TestTerrain()
{
}

TestTerrain::~TestTerrain()
{
	release();
}

TestTerrain::TestTerrain(LPDIRECT3DDEVICE9& device) : Engine::GameObject(device) ,transform(nullptr) ,polygon(nullptr) ,texture(nullptr)
{
}

TestTerrain::TestTerrain(const TestTerrain& other) : Engine::GameObject(other), transform(other.transform), polygon(other.polygon), texture(other.texture)
{
}

void TestTerrain::start(void)
{
	polygon = Engine::Polygon::create(device);
	transform = Engine::Transform::create(device);
	std::wstring filePath = L"D:\\Downloads\\nullTexture.jpg";
	texture = Engine::Texture::create(device, filePath);
	filePath = L"D:\\Downloads\\Height1.bmp";

	
	IDirect3DTexture9* heightMapTexture = nullptr;
	D3DXCreateTextureFromFile(device, filePath.c_str(), &heightMapTexture);

	D3DSURFACE_DESC desc;
	int width = 0, height = 0;
	if (SUCCEEDED(heightMapTexture->GetLevelDesc(0, &desc)))
	{
		width = desc.Width;
		height = desc.Height;
	}

	D3DLOCKED_RECT lockedRect;
	heightMapTexture->LockRect(0, &lockedRect, NULL, D3DLOCK_READONLY);
	//BYTE* data = static_cast<BYTE*>(lockedRect.pBits);
	//DWORD* pixelData = reinterpret_cast<DWORD*>(data);
	DWORD* pixelData = reinterpret_cast<DWORD*>(static_cast<BYTE*>(lockedRect.pBits));

	std::vector<Engine::tVertex> vertexes = {};
	std::vector<Engine::vIndex> indexes = {};

	for (int z = 0; z < height; ++z)
	{
		for (int x = 0; x < width; ++x)
		{
			Vector3 position = { static_cast<float>(x), static_cast<float>(pixelData[z * (lockedRect.Pitch / 4) + x] & 0xFF), static_cast<float>(z) };
			vertexes.push_back({
				position, {static_cast<float>(x) / static_cast<float>(width - 1), static_cast<float>(z) / static_cast<float>(height - 1)}
				});
			nodePosition.push_back(position);
		}
	}
	heightMapTexture->UnlockRect(0);
	heightMapTexture->Release();
	 
	for (int y = 0; y < height - 1; y += 1)
	{
		for (int x = 0; x < width - 1; x += 1)
		{
			indexes.push_back({ static_cast<unsigned short>(x + y * width),	static_cast<unsigned short>((x + 1) + (y + 1) * width),	static_cast<unsigned short>(x + (y + 1) * width) });
			indexes.push_back({ static_cast<unsigned short>(x + y * width),	static_cast<unsigned short>((x + 1) + y * width),		static_cast<unsigned short>((x + 1) + (y + 1) * width) });
		}
	}

	polygon->createPolygon(vertexes, indexes, true);

	transform->scale = { 1.0f, 0.1f,1.0f };
}

void TestTerrain::awake(void)
{
	transform->scale = {1.0f, 0.1f,1.0f };
	transform->position = {0.0f, 0.0f,0.0f };

}

void TestTerrain::update(void)
{
}

void TestTerrain::lateUpdate(void)
{
}

void TestTerrain::fixedUpdate(void)
{
}

void TestTerrain::render(void)
{
	transform->scale = { 1.0f, 0.1f,1.0f };
	//device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	transform->update();
	transform->applyWorldMatrix();
	texture->setTexture(0);
	polygon->render();
	//device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void TestTerrain::release(void)
{
	if (transform)
	{
		transform->release();
		delete transform;
		transform = nullptr;
	}
	if (polygon)
	{
		polygon->release();
		delete polygon;
		polygon = nullptr;
	}
	if (texture)
	{
		texture->release();
		delete texture;
		texture = nullptr;
	}
}

TestTerrain* TestTerrain::create(LPDIRECT3DDEVICE9& _device)
{
	TestTerrain* newTerrain = new TestTerrain(_device);
	newTerrain->start();
	newTerrain->awake();
	return newTerrain;
}

Engine::GameObject* TestTerrain::clone(void)
{
	return nullptr;
}
