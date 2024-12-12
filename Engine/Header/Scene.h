#pragma once
#include "Base.hpp"
#include "Layer.h"

namespace Engine
{
	class ENGINE_DLL Scene : public Base
	{
	public:
		Scene(void);
		virtual ~Scene(void);

		virtual void release(void);
		virtual void start(void);
		virtual void awake(void);
		virtual void update(void);
		virtual void lateUpdate(void);
		virtual void fixedUpdate(void);
		virtual void render(void);

		Component* findComponent(std::wstring layerName, std::wstring objectName, std::wstring componentName);
		Component* findComponent(std::wstring componentName);
		GameObject* findGameObject(std::wstring layerName, std::wstring objectName);
		GameObject* findGameObject(std::wstring objectName);
		Layer* findLayer(std::wstring layerName);
		
		void addLayer(Layer* layer, std::wstring layerName);
		void addLayer(std::wstring layerName);
	protected:
		std::map<std::wstring, Layer*> layers;


	};

}