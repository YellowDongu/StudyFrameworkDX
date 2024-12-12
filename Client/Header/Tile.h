#pragma once
#include "GameObject.h"


class Tile : public Engine::GameObject
{
public:
	Tile();
	virtual ~Tile();
	Tile(LPDIRECT3DDEVICE9& _device);
	Tile(Tile& other);

	static Tile* create(LPDIRECT3DDEVICE9& _device, std::wstring& _filePath);

	virtual void start(void) override;
	virtual void awake(void) override;
	virtual void render(void) override;
	virtual void release(void) override;

	HRESULT changeTexture(std::wstring& _filePath);
	Engine::Transform* transform() { return _transform; }

	GameObject* clone(void) override;
private:
	std::wstring filePath;
	
	Engine::Texture* tileTexture;
	Engine::Polygon* polygon;
	Engine::Transform* _transform;
};