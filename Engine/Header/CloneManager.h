#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Texture.h"

namespace Engine
{
	class ENGINE_DLL CloneManager : public Base
	{
	public:
		CloneManager();
		virtual ~CloneManager();

		static CloneManager* create(LPDIRECT3DDEVICE9& _device);

		HRESULT createTexture(std::wstring filePath, std::wstring name, bool cube = false);
		HRESULT createTexture(std::vector<std::wstring> filePath, std::wstring name, bool cube = false);

		void addComponent(Component* component, std::wstring name);
		void addGameObject(GameObject* gameObject, std::wstring name);

		Component* cloneComponent(std::wstring& name);
		GameObject* cloneGameObject(std::wstring& name);
		Texture* getTexture(std::wstring& textureName);

		void start(void);
		void release(void) override;


	private:


		LPDIRECT3DDEVICE9 device;

		std::map<std::wstring, Component*> componentInstance;
		std::map<std::wstring, GameObject*> gameObjectInstance;
		std::map<std::wstring, Texture*> textureInstance;
	};
}
