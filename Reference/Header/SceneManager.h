#pragma once
#include "Scene.h"

namespace Engine
{
	class DXDevice;

	class ENGINE_DLL SceneManager : public Base
	{
	public:
		SceneManager(void);
		virtual ~SceneManager(void);
		SceneManager(const SceneManager&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;

		static SceneManager* create(Scene* firstScene, std::wstring sceneName);

		Component* findComponent(const std::wstring& LayerName, const std::wstring& objectName, const std::wstring& ComponentName);
		Component* findComponent(const std::wstring& ComponentName);


		virtual void start(void);
		virtual void awake(void);
		virtual void update(void);
		virtual void lateUpdate(void);
		virtual void fixedUpdate(void);
		virtual void render(void);
		virtual void release(void);

		void changeScene(const std::wstring& SceneName);
		const bool& currentSceneExsist(void) const { return currentScene; }
		void addScene(Scene* scene, std::wstring sceneName) { if (!scene) return; scenes[sceneName] = scene; }
	private:
		Scene* currentScene;
		std::map<std::wstring, Scene*> scenes;
	};



}
