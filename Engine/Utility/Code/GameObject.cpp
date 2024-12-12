#include "Engine_base.h"
#include "GameObject.h"

using namespace Engine;


GameObject::GameObject(void) : isClone(false), device(nullptr), components{}
{
}

GameObject::GameObject(LPDIRECT3DDEVICE9& device) : isClone(false), device(device), components{}
{
}

GameObject::GameObject(const GameObject& other) : isClone(true), device(other.device), components{}
{
	for (auto& component : other.components)
	{
		components[component.first] = component.second->clone();
	}
}

GameObject::~GameObject(void)
{
	release();
}

void GameObject::update(void)
{
	for (auto& component : components)
	{
		component.second->update();
	}
}

void GameObject::lateUpdate(void)
{
	for (auto& component : components)
	{
		component.second->update();
	}
}


void GameObject::render(void)
{
	for (auto& component : components)
	{
		component.second->update();
	}
}

Component* GameObject::getComponent(const std::wstring& componentName)
{
	auto result = components.find(componentName);
	if(result == components.end())
		return nullptr;
	return (*result).second;
}

void GameObject::release(void)
{
	if (isClone)
		return;
	for (auto& component : components)
	{
		component.second->release();
		delete component.second;
	}
	components.clear();
}
