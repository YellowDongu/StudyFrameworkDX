#include "Engine_base.h"
#include "Scene.h"

using namespace Engine;

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::release()
{
	for (auto& layer : layers)
	{
		for (auto& gameObject : layer.second->gameObjectList())
		{
			gameObject.second->release();
			delete gameObject.second;
		}
		layer.second->gameObjectList().clear();
	}
	layers.clear();
}

void Scene::start(void)
{
	for (auto& layer : layers)
	{
		for (auto& gameObject : layer.second->gameObjectList())
		{
			gameObject.second->start();
		}
	}
}

void Scene::awake(void)
{
	for (auto& layer : layers)
	{
		for (auto& gameObject : layer.second->gameObjectList())
		{
			gameObject.second->awake();
		}
	}
}

void Scene::update(void)
{
	for (auto& layer : layers)
	{
		for (auto& gameObject : layer.second->gameObjectList())
		{
			gameObject.second->update();
		}
	}
}

void Scene::lateUpdate(void)
{
	for (auto& layer : layers)
	{
		for (auto& gameObject : layer.second->gameObjectList())
		{
			gameObject.second->lateUpdate();
		}
	}
}

void Scene::fixedUpdate(void)
{
	for (auto& layer : layers)
	{
		for (auto& gameObject : layer.second->gameObjectList())
		{
			gameObject.second->fixedUpdate();
		}
	}
}

void Scene::render(void)
{
	for (auto& layer : layers)
	{
		for (auto& gameObject : layer.second->gameObjectList())
		{
			gameObject.second->render();
		}
	}
}

Component* Scene::findComponent(std::wstring layerName, std::wstring objectName, std::wstring componentName)
{
	Layer* layer = findLayer(layerName);
	if (!layer)
		return nullptr;

	return layer->findComponent(layerName, objectName);
}

// 쓰지않는걸 권장함
Component* Scene::findComponent(std::wstring componentName)
{
	for (auto layer : layers)
	{
		Component* result = layer.second->findComponent(componentName);
		if (result)
			return result;
	}

	return nullptr;
}

GameObject* Scene::findGameObject(std::wstring layerName, std::wstring objectName)
{
	Layer* layer = findLayer(layerName);
	if(!layer)
		return nullptr;

	return layer->findGameObject(objectName);
}

// 쓰지않는걸 권장함
GameObject* Scene::findGameObject(std::wstring objectName)
{
	for (auto layer : layers)
	{
		GameObject* result = layer.second->findGameObject(objectName);
		if (result)
			return result;
	}
	return nullptr;
}

Layer* Scene::findLayer(std::wstring layerName)
{
	auto result = layers.find(layerName);
	if(result == layers.end())
		return nullptr;
	return (*result).second;

}

void Engine::Scene::addLayer(Layer* layer, std::wstring layerName)
{
	if (layers.find(layerName) != layers.end())
		return;
	layers[layerName] = layer;
}

