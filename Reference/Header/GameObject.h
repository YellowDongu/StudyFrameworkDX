#pragma once
#include "Base.hpp"
#include "Component.h"

namespace Engine
{
	class ENGINE_DLL GameObject : public Base
	{
	public:
		GameObject(void);
		virtual ~GameObject(void);
		GameObject(LPDIRECT3DDEVICE9& device);
		GameObject(const GameObject& other);

		virtual void start(void) {}
		virtual void awake(void) {}
		virtual void update(void);
		virtual void lateUpdate(void);
		virtual void fixedUpdate(void) {}
		virtual void render(void);
		virtual void release(void);

		virtual GameObject* clone(void) = 0;

		Component* getComponent(const std::wstring& componentName);


	protected:
		bool isClone;
		LPDIRECT3DDEVICE9 device;
		std::map<std::wstring, Component*> components;


	};

}