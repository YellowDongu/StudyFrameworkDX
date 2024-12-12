#pragma once
#include "GameObject.h"
#include "Camera.h"

class Player : public Engine::GameObject
{
public:
	Player(void);
	virtual ~Player(void);
	Player(LPDIRECT3DDEVICE9& _device);
	Player(Player& player);

	virtual void start(void) override;
	virtual void update(void) override;

	virtual GameObject* clone(void);

	static Player* create(LPDIRECT3DDEVICE9& _device);
private:
	bool innerTriangle(const Vector3& currentPoint, const Vector3& vertice1, const Vector3& vertice2, const Vector3& vertice3);
	float planeYCalculate(const Vector3& currentPoint, const Vector3& vertice1, const Vector3& vertice2, const Vector3& vertice3);


	//testArea
public:
	void controlCamera(void);

	std::vector<Vector3>* terrainPos;

	Engine::Camera* camera = nullptr;
	std::shared_ptr<Engine::InputManager> input = nullptr;
	std::shared_ptr<Engine::TimeManager> Time = nullptr;
	//testArea
};
