#include "Engine_base.h"
#include "Layer.h"

using namespace Engine;

Layer::Layer(void)
{
}

Layer::~Layer(void)
{
	release();
}

void Layer::release(void)
{
}

Component* Layer::findComponent(std::wstring objectName, std::wstring componentName)
{
	GameObject* gameObject = findGameObject(objectName);
	if(!gameObject)
		return nullptr;
	
	return gameObject->getComponent(componentName);
}

// 쓰지않는걸 권장함
Component* Layer::findComponent(std::wstring componentName)
{
	for (auto gameObject : gameObjects)
	{
		Component* result = gameObject.second->getComponent(componentName);
		if (result)
			return result;
	}
	return nullptr;
}

GameObject* Layer::findGameObject(std::wstring objectName)
{
	auto result = gameObjects.find(objectName);
	if(result == gameObjects.end())
		return nullptr;
	return (*result).second;
}

void Layer::addGameObject(GameObject* object, std::wstring objectName)
{
	auto result = gameObjects.find(objectName);
	if (result == gameObjects.end())
		return;

	gameObjects[objectName] = object;
}

Layer* Layer::create()
{
	return new Layer();
}
