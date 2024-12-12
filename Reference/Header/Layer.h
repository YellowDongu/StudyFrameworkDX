#pragma once
#include "Base.hpp"
#include "GameObject.h"

namespace Engine
{

	class ENGINE_DLL Layer : public Base
	{
	public:
		Layer(void);
		virtual ~Layer(void);

		virtual void release(void);

		Component* findComponent(std::wstring objectName, std::wstring componentName);
		Component* findComponent(std::wstring componentName);
		GameObject* findGameObject(std::wstring objectName);
		void addGameObject(GameObject* object, std::wstring objectName);

		static Layer* create();
		std::map<std::wstring, GameObject*>& gameObjectList() { return gameObjects; }
	private:
		std::map<std::wstring, GameObject*> gameObjects;


	};
}