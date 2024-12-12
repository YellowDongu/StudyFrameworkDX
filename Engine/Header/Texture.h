#pragma once
#include "Component.h"

namespace Engine
{
	// 텍스쳐 매니저로 같은 텍스쳐를 두곳에서 따로따로 로드해서 메모리 쳐먹는거 억제해야됨
	class ENGINE_DLL Texture : public Component
	{
	public:
		Texture();
		virtual ~Texture();
		Texture(LPDIRECT3DDEVICE9& _device);
		Texture(Texture& other);

		void release(void) override;
		Component* clone(void) override;
		static Texture* create(LPDIRECT3DDEVICE9& _device, const std::wstring& filePath, bool cube = false);
		static Texture* create(LPDIRECT3DDEVICE9& _device, const std::vector<std::wstring>& filePath, bool cube = false);

		HRESULT loadTexture(const std::wstring& filePath, bool cube = false);
		void setTexture(const int& iIndex);
	private:

		std::vector<IDirect3DBaseTexture9*> textures;


	};
}