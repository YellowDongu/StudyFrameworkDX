#pragma once
#include "Component.h"

namespace Engine
{
	class ENGINE_DLL Polygon : public Component
	{
	public:
		explicit Polygon(void);
		explicit Polygon(LPDIRECT3DDEVICE9& _device);
		explicit Polygon(const Polygon& other);
		virtual ~Polygon(void);

		virtual void render(void);
		virtual void release(void);

		void createPolygon(const std::vector<SimpleVertex>& vertex, const std::vector<VertexIndex>& index, unsigned long _triangleCount, bool notRHW = true);
		void createPolygon(const std::vector<SimpleVertex>& vertex, unsigned long& _triangleCount, bool rhw = true);
		void createPolygon(const std::vector<TextureVertex>& vertex, const std::vector<VertexIndex>& index, unsigned long& _triangleCount, bool notRHW = true);
		void createPolygon(const std::vector<TextureVertex>& vertex, const std::vector<VertexIndex>& index, bool rhw = true);
		void createPolygon(const std::vector<Texture3dVertex>& vertex, const std::vector<VertexIndex>& index, bool rhw = true);
		void createPolygon(const std::vector<Texture3dVertex>& vertex, const std::vector<VertexIndex>& index, unsigned long& _triangleCount, bool notRHW = true);

		static Polygon* create(LPDIRECT3DDEVICE9 _device);
		virtual Component* clone(void);

	private:
		unsigned long vertexSize;
		unsigned long vertexCount;
		unsigned long triangleCount;
		unsigned long fvf;

		Matrix* worldMatrix;

		LPDIRECT3DVERTEXBUFFER9		vertexBuffer;
		LPDIRECT3DINDEXBUFFER9		indexBuffer;
	};

}