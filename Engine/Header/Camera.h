#pragma once
#include "GameObject.h"

// ÄÄÆ÷³ÍÆ®·Î ¹Ù²Ü ¿¹Á¤

namespace Engine
{
	class Transform;

	class ENGINE_DLL Camera : public GameObject
	{
	public:
		Camera(void);
		virtual ~Camera(void);
		Camera(LPDIRECT3DDEVICE9& _device);
		Camera(const Camera& other);

		virtual void start(void);
		virtual void update(void);
		virtual void release(void);

		virtual GameObject* clone(void);

		void getWindowInfo(void);
		static Camera* create(HWND _hWnd, LPDIRECT3DDEVICE9 _device);

		void setFOV(float value) { fov = value; }
		void setNearSightRange(float value) { nearSightRange = value; }
		void setMaximumSightRange(float value) { maximumSightRange = value; }

		const float& GetFOV(void) const { return fov; }
		const float& getMaximumSightRange(void) const { return maximumSightRange; }
		Transform* transform() { return transformComponent; }
		const Vector3& forward() const { return directionZ; }

		void localRotate(Vector3 rotationRadian);
	private:
		float fov;
		float aspectRatio;
		float nearSightRange, maximumSightRange;

		HWND hWnd;
		Transform* transformComponent;

		Vector2 windowSize;
		Vector3 direction, up, at;
		Vector3 directionX, directionY, directionZ;
		Matrix viewMatrix, projectionMatrix;
	};

}