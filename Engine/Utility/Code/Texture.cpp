#include "Engine_base.h"
#include "Texture.h"

using namespace Engine;


Texture::Texture()
{
}

Texture::~Texture()
{
	release();
}

Texture::Texture(LPDIRECT3DDEVICE9& _device) : Component(_device), textures{}
{
}

Texture::Texture(Texture& other) : Component(other), textures(other.textures)
{
}

void Texture::release(void)
{
	if (isClone)
		return;
	for (auto texture : textures)
	{
		texture->Release();
	}
	textures.clear();
}
Component* Texture::clone(void)
{
	return new Texture(*this);
}

Texture* Texture::create(LPDIRECT3DDEVICE9& _device, const std::vector<std::wstring>& filePath, bool cube)
{
	Texture* newTexture = new Texture(_device);
	for (auto& file : filePath)
	{
		if (FAILED(newTexture->loadTexture(file, cube)))
		{
			newTexture->release();
			delete newTexture;
			return nullptr;
		}
	}

	return newTexture;
}

Texture* Texture::create(LPDIRECT3DDEVICE9& _device, const std::wstring& filePath, bool cube)
{
	Texture* newTexture = new Texture(_device);
	if (FAILED(newTexture->loadTexture(filePath, cube)))
	{
		newTexture->release();
		delete newTexture;
		return nullptr;
	}

	return newTexture;
}

HRESULT Texture::loadTexture(const std::wstring& filePath, bool cube)
{
	if (!device)
		return E_FAIL;
	IDirect3DBaseTexture9* newTexture = nullptr;

	HRESULT result;
	if (cube)
		result = D3DXCreateCubeTextureFromFile(device, filePath.c_str(), (LPDIRECT3DCUBETEXTURE9*)&newTexture);
	else
		result = D3DXCreateTextureFromFile(device, filePath.c_str(), (LPDIRECT3DTEXTURE9*)&newTexture);

	if(FAILED(result))
	{
		std::wstring error = L"Texture Load Error : " + filePath;
		PopUp(error.c_str());
		return E_FAIL;
	}

	textures.push_back(newTexture);
	return S_OK;
}

void Texture::setTexture(const int& index)
{
	if (textures.empty() || !device || textures.size() < index)
	{
		std::wstring error = L"Texture Index Error : " + index;
		PopUp(error.c_str());
		return;
	}

	device->SetTexture(0, textures[index]);
}
