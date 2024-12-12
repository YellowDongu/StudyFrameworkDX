#pragma once
#include "GameObject.h"

class Skybox : public Engine::GameObject
{
public:
	Skybox(void);
	virtual ~Skybox(void);
	Skybox(LPDIRECT3DDEVICE9& device);
	Skybox(const Skybox& other);

	virtual void start(void);
	virtual void awake(void);
	virtual void update(void);
	virtual void lateUpdate(void);
	virtual void fixedUpdate(void);
	virtual void render(void);
	virtual void release(void);
	virtual GameObject* clone(void);

	static Skybox* create(LPDIRECT3DDEVICE9& device);

	void setPosition(Vector3 value) { transform->position = value; }
private:
	Engine::Texture* texture;
	Engine::Transform* transform;
	Engine::Polygon* polygon;

};


