#pragma once
#include "GameObject.h"
#include "tile.h"

class TileManager : public Engine::GameObject
{
public:
	TileManager(void);
	virtual ~TileManager(void);
	TileManager(LPDIRECT3DDEVICE9 _device);

	static TileManager* create(LPDIRECT3DDEVICE9 _device, int x, int y, float tileSize);


	virtual void start(void) override;
	virtual void awake(void) override;
	virtual void render(void) override;
	virtual void release(void) override;

	Tile* GetTile(float index);
	Tile* GetTile(float _x, float _y);

	GameObject* clone(void) override;
private:
	int xMax, yMax;
	//Vector3 tileSize;
	float tileSize;

	std::vector<Tile*> tiles;


};

TileManager::TileManager(void) : xMax(0), yMax(0), tileSize(0.0f), tiles{}
{
}

TileManager::~TileManager(void)
{
	release();
}

TileManager::TileManager(LPDIRECT3DDEVICE9 _device) : GameObject(_device), xMax(0), yMax(0), tileSize(0.0f), tiles{}
{
}

TileManager* TileManager::create(LPDIRECT3DDEVICE9 _device, int x, int y, float _tileSize)
{
	TileManager* newTileManager = new TileManager(_device);
	newTileManager->xMax = x;
	newTileManager->yMax = y;
	newTileManager->tileSize = _tileSize;
	newTileManager->start();

	if(newTileManager->tiles.empty())
		return nullptr;
	return newTileManager;
}

void TileManager::start(void)
{
	for (int y = 0; y < yMax; y++)
	{
		for (int x = 0; x < xMax; x++)
		{
			std::wstring filePath = L"D:\\Downloads\\nullTexture.jpg";
			Tile* newTile = Tile::create(device, filePath);
			if (!newTile)
			{
				release();
				return;
			}

			tiles.push_back(newTile);
			newTile->start();
			newTile->transform()->position = {(float)x * tileSize, 0.0f, (float)y * tileSize };
		}
	}
}

void TileManager::awake(void)
{
	for (auto& tile : tiles)
	{
		tile->awake();
	}

}
void TileManager::render(void)
{
	for (auto& tile : tiles)
	{
		tile->render();
	}

}

void TileManager::release(void)
{
	if (isClone)
		return;
	for (auto& tile : tiles)
	{
		tile->release();
		delete tile;
	}
	tiles.clear();
}

Tile* TileManager::GetTile(float index)
{
	if(index >= tiles.size())
		return nullptr;
	return tiles[index];
}

Tile* TileManager::GetTile(float _x, float _y)
{
	if(_x < 0 || _x >= xMax || _y < 0 || _y >= yMax)
		return nullptr;
	return tiles[_x * xMax + _y];
}

Engine::GameObject* TileManager::clone(void)
{
	return nullptr;
}
