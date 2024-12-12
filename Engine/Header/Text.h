#pragma once
#include "Component.h"

namespace Engine
{
	class ENGINE_DLL Text : public Component
	{
	public:
		explicit Text(void);
		virtual ~Text(void);
		explicit Text(LPDIRECT3DDEVICE9& _device);
		explicit Text(const Text& other);

		virtual void start(void) override;
		virtual void awake(void) override;
		virtual void update(void) override;
		virtual void lateUpdate(void) override;
		virtual void fixedUpdate(void) override;
		virtual void release(void) override;
		virtual void render(void) override;
		virtual Component* clone(void) override;

		static Text* create(LPDIRECT3DDEVICE9& _device, std::wstring text, Vector2 _position, BYTE _charSet = HANGEUL_CHARSET, std::wstring fontType = L"πŸ≈¡", unsigned int _textWidth = 12, unsigned int _textHeight = 12, unsigned int _textWeight = FW_THIN);
		HRESULT createFont(std::wstring pFontType, unsigned int _textWidth = 12, unsigned int _textHeight = 12, unsigned int _textWeight = FW_THIN);
		void setPosition(Vector2 value) { position = value; }
		void setText(std::wstring value) { text = value; }
		void setColor(D3DXCOLOR value) { textColor = value; }

		const std::wstring& getText(void) const { return text; }
		const Vector2& getTextPosition(void) const { return position; }

	private:
		BYTE charSet;
		unsigned int textWidth;
		unsigned int textHeight;
		unsigned int textWeight;
		LPD3DXSPRITE fontSprite;
		LPD3DXFONT font;

		Vector2 position;
		D3DXCOLOR textColor;
		std::wstring text;

	};
}