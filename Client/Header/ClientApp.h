#pragma once
#include "Polygon.h"
#include "Camera.h"

class ClientApp : public Base
{
public:
	explicit ClientApp(void);
	virtual ~ClientApp(void);

private:
	virtual void release();
public:
	static ClientApp* create(void);


	// Methods
	HRESULT initiate(void);
	void frameCycle(void);




private:
	// variable
	Engine::Polygon* rect;
	Engine::SceneManager* sceneManager;
	std::shared_ptr<Engine::DXDevice> device;
};