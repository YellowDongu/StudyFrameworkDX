#include "Engine_Base.h"
#include "Text.h"

using namespace Engine;


Text::Text() : charSet(HANGEUL_CHARSET), textWidth(0), textHeight(0), textWeight(0),
fontSprite(nullptr), font(nullptr), position({ 0.0f,0.0f }), textColor({ 0,0,0,0 }), text(L"")
{
}

Text::~Text()
{
	release();
}


Text::Text(LPDIRECT3DDEVICE9& _device) : Component(_device), charSet(HANGEUL_CHARSET), textWidth(0), textHeight(0), textWeight(0),
fontSprite(nullptr), font(nullptr), position({ 0.0f,0.0f }), textColor({ 0,0,0,0 }), text(L"")
{

}

Text::Text(const Text& other) : Component(other), charSet(HANGEUL_CHARSET), textWidth(0), textHeight(0), textWeight(0), 
	fontSprite(nullptr), font(nullptr), position({ 0.0f,0.0f }), textColor({0,0,0,0}), text(L"")
{

}


void Text::start(void)
{

}

void Text::awake(void)
{

}

void Text::update(void)
{

}

void Text::lateUpdate(void)
{

}

void Text::fixedUpdate(void)
{

}

void Text::release(void)
{
	if(font)
		font->Release();
	if (fontSprite)
	fontSprite->Release();
}

void Text::render(void)
{
	RECT textRectangle = { (long)position.x, (long)position.y };

	fontSprite->Begin(D3DXSPRITE_ALPHABLEND);

	font->DrawTextW(fontSprite, text.c_str(), lstrlen(text.c_str()), &textRectangle, DT_NOCLIP, textColor);

	fontSprite->End();
}

Component* Text::clone(void)
{
	return new Text(*this);
}

Text* Text::create(LPDIRECT3DDEVICE9& _device, std::wstring _text, Vector2 _position, BYTE _charSet, std::wstring fontType, unsigned int _textWidth, unsigned int _textHeight, unsigned int _textWeight)
{
	Text* newText = new Text(_device);
	newText->charSet = _charSet;
	newText->text = _text;
	newText->position = _position;

	if (FAILED(newText->createFont(fontType, _textWidth, _textHeight, _textWeight)))
	{
		newText->release();
		delete newText;
		return nullptr;
	}

	return newText;
}

HRESULT Text::createFont(std::wstring fontType, unsigned int _textWidth, unsigned int _textHeight, unsigned int _textWeight)
{
	textWidth = _textWidth;
	textHeight = _textHeight;
	textWeight = _textWeight;

	D3DXFONT_DESC fontDesc;
	ZeroMemory(&fontDesc, sizeof(D3DXFONT_DESC));
	if (charSet == 0)
		fontDesc.CharSet = HANGEUL_CHARSET;
	else
		fontDesc.CharSet = charSet;
	fontDesc.Width = textWidth;
	fontDesc.Height = textHeight;
	fontDesc.Weight = textWeight;
	lstrcpy(fontDesc.FaceName, fontType.c_str());

	if (FAILED(D3DXCreateFontIndirect(device, &fontDesc, &font)))
	{
		PopUp((std::wstring(L"Font Create Error : ") + fontType).c_str());
		return E_FAIL;
	}

	if (FAILED(D3DXCreateSprite(device, &fontSprite)))
	{
		PopUp((std::wstring(L"Font_Sprite Create Error : ") + fontType).c_str());
		return E_FAIL;
	}

	return S_OK;
}