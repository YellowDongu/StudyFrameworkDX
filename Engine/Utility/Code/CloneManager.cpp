#include "Engine_base.h"
#include "CloneManager.h"

#include "Polygon.h"
#include "Texture.h"
#include "Transform.h"
#include "Texture.h"





using namespace Engine;

CloneManager::CloneManager() : componentInstance{}, gameObjectInstance{}, device(nullptr)
{
}

CloneManager::~CloneManager()
{
	release();
}

CloneManager* CloneManager::create(LPDIRECT3DDEVICE9& _device)
{
	CloneManager* newCloneManager = new CloneManager();
	newCloneManager->device = _device;
	return newCloneManager;
}

HRESULT CloneManager::createTexture(std::wstring filePath, std::wstring name, bool cube)
{
	Texture* texture = Texture::create(device, filePath);

	if(!texture)
	return E_FAIL;

	textureInstance[name] = texture;
	return S_OK;
}

HRESULT CloneManager::createTexture(std::vector<std::wstring> filePath, std::wstring name, bool cube)
{
	Texture* texture = Texture::create(device, filePath);

	if (!texture)
		return E_FAIL;

	textureInstance[name] = texture;
	return S_OK;
}

void CloneManager::addComponent(Component* component, std::wstring name)
{
	componentInstance[name] = component;
}

void CloneManager::addGameObject(GameObject* gameObject, std::wstring name)
{
	gameObjectInstance[name] = gameObject;
}

void CloneManager::start(void)
{
	Transform* blankTransform = Transform::create(device);
	Polygon* blankPolygon = Polygon::create(device);
}

void CloneManager::release(void)
{
	for (auto& instance : componentInstance)
	{
		instance.second->release();
		delete instance.second;
	}

	for (auto& instance : gameObjectInstance)
	{
		instance.second->release();
		delete instance.second;
	}

	for (auto& instance : textureInstance)
	{
		instance.second->release();
		delete instance.second;
	}
}


Component* CloneManager::cloneComponent(std::wstring& name)
{
	auto result = componentInstance.find(name);
	if (result == componentInstance.end())
	{
		PopUp((std::wstring(L"No Component Found! : ") + name).c_str());
		return nullptr;
	}
	return (*result).second->clone();
}
GameObject* CloneManager::cloneGameObject(std::wstring& name)
{
	auto result = gameObjectInstance.find(name);
	if (result == gameObjectInstance.end())
	{
		PopUp((std::wstring(L"No GameObject Found! : ") + name).c_str());
		return nullptr;
	}
	return (*result).second->clone();
}
Texture* CloneManager::getTexture(std::wstring& textureName)
{
	auto result = textureInstance.find(textureName);
	if (result == textureInstance.end())
	{
		PopUp((std::wstring(L"No Texture Found! : ") + textureName).c_str());
		return nullptr;
	}
	return (Texture*)(*result).second->clone();
}