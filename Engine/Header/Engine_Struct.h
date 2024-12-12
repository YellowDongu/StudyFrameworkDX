#pragma once
#ifndef Engine_Struct_h__
#define Engine_Struct_h__

#include "Engine_TypeDef.h"

namespace Engine
{
	typedef struct SimpleVertex
	{
		Vector3		position;
		ULONG		color;

	}sVertex;

#define simpleFVF  (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0)
#define simpleFVFRHW (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX0)

	typedef struct TextureVertex
	{
		Vector3		position;
		Vector2		texturePosition;

	}tVertex;

#define textureFVF (D3DFVF_XYZ | D3DFVF_TEX1)
#define textureFVFRHW (D3DFVF_XYZRHW | D3DFVF_TEX1)

	typedef struct AdditionalTextureVertex
	{
		Vector3		position;
		Vector3		normalVector;
		Vector2		texturePosition;

	}ATVertex;

#define AdditionalTextureFVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)
#define AdditionalTextureFVFRHW (D3DFVF_XYZRHW |D3DFVF_NORMAL | D3DFVF_TEX1)
#define atFVF AdditionalTextureFVF
#define atFVFRHW AdditionalTextureFVFRHW

	typedef struct Texture3dVertex
	{
		Vector3		position;
		Vector3		texturePosition;

	}t3dVertex;

#define Texture3dFVF (D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0)) // �ؽ�ó�� UV ��ǥ ���� FLOAT�� 3���� ǥ���ϰڴٴ� ��ũ��(��ȣ���� ���� 0�� �ǹ̴� ���� ���ؽ��� �ؽ��� UV���� �������� �� �� �ִµ� ���� 0��° ���� �����ϰڴٴ� �ǹ�)
#define Texture3dFVFRHW (D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0)) // �ؽ�ó�� UV ��ǥ ���� FLOAT�� 3���� ǥ���ϰڴٴ� ��ũ��(��ȣ���� ���� 0�� �ǹ̴� ���� ���ؽ��� �ؽ��� UV���� �������� �� �� �ִµ� ���� 0��° ���� �����ϰڴٴ� �ǹ�)

	typedef struct VertexIndex
	{
		USHORT  _0;
		USHORT  _1;
		USHORT  _2;

	}VertexIndex16, vIndex16, vIndex;

	typedef struct VertexIndex32
	{
		ULONG	_0;
		ULONG	_1;
		ULONG	_2;

	}vIndex32;




}


#endif // Engine_Struct_h__
