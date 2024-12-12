#pragma once
//#include "GameObject.h"

class TestTerrain : public Engine::GameObject
{
public:
	TestTerrain();
	virtual ~TestTerrain();
	TestTerrain(LPDIRECT3DDEVICE9& _device);
	TestTerrain(const TestTerrain& other);

	virtual void start(void);
	virtual void awake(void);
	virtual void update(void);
	virtual void lateUpdate(void);
	virtual void fixedUpdate(void);
	virtual void render(void);
	virtual void release(void);

	static TestTerrain* create(LPDIRECT3DDEVICE9& _device);
	GameObject* clone(void) override;

	std::vector<Vector3>* linkNodeList(void) { return &nodePosition; }
private:
	Engine::Transform* transform;
	Engine::Polygon* polygon;
	Engine::Texture* texture;

	std::vector<Vector3> nodePosition;
};
