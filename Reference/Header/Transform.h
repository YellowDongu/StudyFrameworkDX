#pragma once
#include "Component.h"

namespace Engine
{
	class ENGINE_DLL Transform : public Component
	{
	public:
		explicit Transform(void);
		explicit Transform(LPDIRECT3DDEVICE9& _device);
		explicit Transform(const Transform& origin);
		virtual ~Transform(void);

		static Transform* create(LPDIRECT3DDEVICE9& _device);

		virtual void update(void);
		virtual void start(void);
		virtual void release(void);
		virtual Component* clone(void) override;

		void initializeValue(void);
		void applyWorldMatrix(void) { device->SetTransform(D3DTS_WORLD, &worldMatrix); }
		const Matrix& getWorldMatrix(void) const { return worldMatrix; }
	public:
		Vector3 scale;
		Vector3 rotation;
		Vector3 position;
	private:
		Vector3 calculateVector[3];
		Matrix worldMatrix;

	};

}