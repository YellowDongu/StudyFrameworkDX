#pragma once
#include "GameObject.h"


class Engine::Texture;
class Engine::Transform;
class Engine::Polygon;


class TestObject : public Engine::GameObject
{
public:
	TestObject(void);
	virtual ~TestObject(void);

	virtual void start(void) override;
	virtual void update(void) override;
	virtual void render(void) override;


	static TestObject* create(LPDIRECT3DDEVICE9 device);
	GameObject* clone(void) override;

	Engine::Transform* transform(void) { return transformComponent; }
	void setDestination(Vector3 value) { isMoving = true; destination = value; }
	void linkTerrainVertex(std::vector<Vector3>* target) { terrainPos = target; }
private:
	bool innerTriangle(const Vector3& currentPoint, const Vector3& vertice1, const Vector3& vertice2, const Vector3& vertice3);
	float planeYCalculate(const Vector3& currentPoint, const Vector3& vertice1, const Vector3& vertice2, const Vector3& vertice3);

	bool isMoving;
	Vector3 destination;
	std::vector<Vector3>* terrainPos;

	Engine::Texture* texture;
	Engine::Transform* transformComponent;
	Engine::Transform* cameraTransformComponent;
	Engine::Polygon* polygon;

	//testArea
public:

	std::shared_ptr<Engine::InputManager> input = nullptr;
	std::wstring debugText;
};
