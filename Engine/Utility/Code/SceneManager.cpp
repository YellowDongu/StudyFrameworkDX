#include "Engine_base.h"
#include "SceneManager.h"

using namespace Engine;

SceneManager::SceneManager(void) : scenes{}, currentScene(nullptr)
{
}

SceneManager::~SceneManager(void)
{
	release();
}

SceneManager* SceneManager::create(Scene* firstScene, std::wstring sceneName)
{
	if (!firstScene)
		return nullptr;
	SceneManager* newSceneManager = new SceneManager();
	newSceneManager->currentScene = firstScene;
	newSceneManager->scenes[sceneName] = firstScene;
	firstScene->start();
	return newSceneManager;
}

Component* SceneManager::findComponent(const std::wstring& LayerName, const std::wstring& objectName, const std::wstring& ComponentName)
{
	if(!currentScene)
		return nullptr;

	return currentScene->findComponent(LayerName, objectName, ComponentName);
}

Component* SceneManager::findComponent(const std::wstring& ComponentName)
{
	if (!currentScene)
		return nullptr;

	return currentScene->findComponent(ComponentName);
}

void SceneManager::start(void)
{
	currentScene->start();
}

void SceneManager::awake(void)
{
	currentScene->awake();
}

void SceneManager::update(void)
{
	currentScene->update();
}

void SceneManager::lateUpdate(void)
{
	currentScene->lateUpdate();
}

void SceneManager::fixedUpdate(void)
{
	currentScene->fixedUpdate();
}

void SceneManager::render(void)
{
	currentScene->render();
}

void SceneManager::release(void)
{
	for (auto scene : scenes)
	{
		delete scene.second;
	}
}

void SceneManager::changeScene(const std::wstring& SceneName)
{
	if (currentScene)
	{
		currentScene->release();
		currentScene->start();
	}

	auto targetScene = scenes.find(SceneName);
	if (targetScene == scenes.end())
		return;

	currentScene = (*targetScene).second;
	currentScene->awake();
}
