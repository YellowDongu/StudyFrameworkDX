#pragma once
#include "Component.h"

namespace Engine
{
	// �ؽ��� �Ŵ����� ���� �ؽ��ĸ� �ΰ����� ���ε��� �ε��ؼ� �޸� �ĸԴ°� �����ؾߵ�
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