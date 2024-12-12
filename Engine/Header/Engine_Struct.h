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

#define Texture3dFVF (D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0)) // 텍스처의 UV 좌표 값을 FLOAT형 3개로 표현하겠다는 매크로(괄호안의 숫자 0의 의미는 본래 버텍스에 텍스쳐 UV값이 여러개가 올 수 있는데 그중 0번째 값을 지정하겠다는 의미)
#define Texture3dFVFRHW (D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0)) // 텍스처의 UV 좌표 값을 FLOAT형 3개로 표현하겠다는 매크로(괄호안의 숫자 0의 의미는 본래 버텍스에 텍스쳐 UV값이 여러개가 올 수 있는데 그중 0번째 값을 지정하겠다는 의미)

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
