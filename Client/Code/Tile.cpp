#include "pch.h"
#include "Tile.h"

Tile::Tile() : filePath(L""), tileTexture(nullptr), polygon(nullptr)
{
}

Tile::~Tile()
{
}

Tile::Tile(LPDIRECT3DDEVICE9& _device) : Engine::GameObject(_device), filePath(L""), _transform(nullptr), tileTexture(nullptr), polygon(nullptr)
{
}

Tile::Tile(Tile& other) : Engine::GameObject(other), filePath(other.filePath), tileTexture(other.tileTexture), polygon(other.polygon), _transform(other._transform)
{
}

Tile* Tile::create(LPDIRECT3DDEVICE9& _device, std::wstring& _filePath)
{
	Tile* newTile = new Tile(_device);
	newTile->device = _device;
	newTile->filePath = _filePath;
	newTile->start();
	if (FAILED(newTile->changeTexture(_filePath)))
	{
		newTile->release();
		delete newTile;
		return nullptr;
	}

	std::vector<Engine::tVertex> vertex = {
	{{ -1.0f, -1.0f,  1.0f },{ 0.f, 0.f }},
	{{  1.0f, -1.0f,  1.0f },{ 1.f, 0.f }},
	{{  1.0f, -1.0f, -1.0f },{ 1.f, 1.f }},
	{{ -1.0f, -1.0f, -1.0f },{ 0.f, 1.f }}
	};
	std::vector<Engine::vIndex> index = {
		{0,3,2},
		{0,2,1}
	};

	newTile->polygon->createPolygon(vertex, index, true);
	return newTile;
}

void Tile::start(void)
{
	tileTexture = new Engine::Texture(device);
	polygon = Engine::Polygon::create(device);
	_transform = Engine::Transform::create(device);
}

void Tile::awake(void)
{
	changeTexture(filePath);
	
}

void Tile::render(void)
{
	_transform->update();
	_transform->applyWorldMatrix();
	tileTexture->setTexture(0);
	polygon->render();
}

void Tile::release(void)
{
	if (tileTexture)
	{
		tileTexture->release();
		delete tileTexture;
		tileTexture = nullptr;
	}
	if (polygon)
	{
		polygon->release();
		delete polygon;
		polygon = nullptr;
	}
}

HRESULT Tile::changeTexture(std::wstring& _filePath)
{
	tileTexture->release();
	return tileTexture->loadTexture(_filePath);
}

Engine::GameObject* Tile::clone(void)
{
	return new Tile(*this);
}
