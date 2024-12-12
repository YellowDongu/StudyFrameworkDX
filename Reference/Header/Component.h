#pragma once
#include "Base.hpp"

namespace Engine
{
	class ENGINE_DLL Component : public Base
	{
	public:
		explicit Component(void);
		explicit Component(LPDIRECT3DDEVICE9& _device);
		explicit Component(const Component& other);
		virtual ~Component(void);



		virtual void start(void) {}
		virtual void awake(void) {}
		virtual void update(void) {}
		virtual void lateUpdate(void) {}
		virtual void fixedUpdate(void) {}
		virtual void render(void) {}

		virtual Component* clone(void) abstract;
	protected:
		bool isClone;
		LPDIRECT3DDEVICE9 device;

	};
}
