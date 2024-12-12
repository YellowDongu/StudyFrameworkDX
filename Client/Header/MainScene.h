#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Player.h"
#include "TestObject.h"
#include "Tile.h"
#include "TestTerrain.h"
#include "Skybox.h"

class MainScene : public Engine::Scene
{
public:
	MainScene(void);
	~MainScene(void);


	virtual void release(void) override;
	virtual void start(void) override;
	virtual void awake(void) override;
	virtual void update(void) override;
	virtual void lateUpdate(void) override;
	virtual void fixedUpdate(void) override;
	virtual void render(void) override;

	static MainScene* create(LPDIRECT3DDEVICE9 _device);
private:
	Player* player;
	TestObject* object;
	LPDIRECT3DDEVICE9 device;
	Tile* testTile;
	TestTerrain* terrain;
	Skybox* skybox;

	std::vector<Engine::Text*> debugTexts;

};
