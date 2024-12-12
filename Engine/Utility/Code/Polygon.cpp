#include "Engine_base.h"
#include "Polygon.h"

using namespace Engine;


Polygon::Polygon() : vertexBuffer(nullptr), indexBuffer(nullptr), worldMatrix(nullptr),
vertexSize(0l), vertexCount(0l), triangleCount(0l), fvf(0l)
{
}

Polygon::Polygon(LPDIRECT3DDEVICE9& _device) : Component(_device),
vertexBuffer(nullptr), indexBuffer(nullptr), worldMatrix(nullptr),
vertexSize(0l), vertexCount(0l), triangleCount(0l), fvf(0l)
{

}

Polygon::Polygon(const Polygon& other) : Component(other),
vertexBuffer(other.vertexBuffer), indexBuffer(other.indexBuffer), worldMatrix(other.worldMatrix),
vertexSize(other.vertexSize), vertexCount(other.vertexCount), triangleCount(other.triangleCount), fvf(other.fvf)
{
}

Polygon::~Polygon(void)
{
}

void Polygon::createPolygon(const std::vector<sVertex>& vertex, const std::vector<vIndex>& index, unsigned long _triangleCount, bool rhw)
{
	if (vertex.empty()) return;
	if (index.empty())
		createPolygon(vertex, _triangleCount, rhw);

	vertexSize = sizeof(sVertex);
	vertexCount = (unsigned long)vertex.size();
	triangleCount = _triangleCount;
	if (rhw)
		fvf = simpleFVFRHW;
	else
		fvf = simpleFVF;

	int vertexTotalSize = vertexCount * vertexSize;
	int indexTotalSize = (int)index.size() * (int)sizeof(vIndex);

	device->CreateVertexBuffer(vertexTotalSize, 0, fvf, D3DPOOL_MANAGED, &vertexBuffer, NULL);
	device->CreateIndexBuffer(indexTotalSize, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, NULL);

	sVertex* vertexData = nullptr;
	vertexBuffer->Lock(0, 0, (void**)&vertexData, 0);
	memcpy(vertexData, vertex.data(), vertexTotalSize);
	vertexBuffer->Unlock();

	vIndex* indexData = nullptr;
	indexBuffer->Lock(0, 0, (void**)&indexData, 0);
	memcpy(indexData, index.data(), indexTotalSize);
	indexBuffer->Unlock();
}

void Polygon::createPolygon(const std::vector<SimpleVertex>& vertex, unsigned long& _triangleCount, bool notRHW)
{
	if (vertex.empty()) return;
	indexBuffer = nullptr;

	vertexSize = sizeof(sVertex);
	vertexCount = (unsigned long)vertex.size();
	triangleCount = _triangleCount;
	if (notRHW)
		fvf = simpleFVF;
	else
		fvf = simpleFVFRHW;

	unsigned long totalSize = vertexCount * vertexSize;

	device->CreateVertexBuffer(totalSize, 0, fvf, D3DPOOL_MANAGED, &vertexBuffer, NULL);

	sVertex* vertexData = nullptr;
	vertexBuffer->Lock(0, 0, (void**)&vertexData, 0);
	memcpy(vertexData, vertex.data(), totalSize);
	vertexBuffer->Unlock();
}

void Polygon::createPolygon(const std::vector<TextureVertex>& vertex, const std::vector<VertexIndex>& index, unsigned long& _triangleCount, bool notRHW)
{

	if (vertex.empty()) return;
	if (index.empty()) return;

	vertexSize = sizeof(tVertex);
	vertexCount = (unsigned long)vertex.size();
	triangleCount = _triangleCount;
	if (notRHW)
		fvf = textureFVF;
	else
		fvf = textureFVFRHW;

	int vertexTotalSize = vertexCount * vertexSize;
	int indexTotalSize = (int)index.size() * (int)sizeof(vIndex);

	device->CreateVertexBuffer(vertexTotalSize, 0, fvf, D3DPOOL_MANAGED, &vertexBuffer, NULL);
	device->CreateIndexBuffer(indexTotalSize, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, NULL);

	tVertex* vertexData = nullptr;
	vertexBuffer->Lock(0, 0, (void**)&vertexData, 0);
	memcpy(vertexData, vertex.data(), vertexTotalSize);
	vertexBuffer->Unlock();

	vIndex* indexData = nullptr;
	indexBuffer->Lock(0, 0, (void**)&indexData, 0);
	memcpy(indexData, index.data(), indexTotalSize);
	indexBuffer->Unlock();
}

void Polygon::createPolygon(const std::vector<TextureVertex>& vertex, const std::vector<VertexIndex>& index, bool notRHW)
{
	if (vertex.empty()) return;
	if (index.empty()) return;

	vertexSize = sizeof(tVertex);
	vertexCount = (unsigned long)vertex.size();
	triangleCount = (unsigned long)index.size();
	if (notRHW)
		fvf = textureFVF;
	else
		fvf = textureFVFRHW;

	int vertexTotalSize = vertexCount * vertexSize;
	int indexTotalSize = (int)index.size() * (int)sizeof(vIndex);

	device->CreateVertexBuffer(vertexTotalSize, 0, fvf, D3DPOOL_MANAGED, &vertexBuffer, NULL);
	device->CreateIndexBuffer(indexTotalSize, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, NULL);

	tVertex* vertexData = nullptr;
	vertexBuffer->Lock(0, 0, (void**)&vertexData, 0);
	memcpy(vertexData, vertex.data(), vertexTotalSize);
	vertexBuffer->Unlock();

	vIndex* indexData = nullptr;
	indexBuffer->Lock(0, 0, (void**)&indexData, 0);
	memcpy(indexData, index.data(), indexTotalSize);
	indexBuffer->Unlock();
}

void Polygon::createPolygon(const std::vector<Texture3dVertex>& vertex, const std::vector<VertexIndex>& index, bool notRHW)
{
	if (vertex.empty()) return;
	if (index.empty()) return;

	vertexSize = sizeof(t3dVertex);
	vertexCount = (unsigned long)vertex.size();
	triangleCount = (unsigned long)index.size();
	if (notRHW)
		fvf = Texture3dFVF;
	else
		fvf = Texture3dFVFRHW;

	int vertexTotalSize = vertexCount * vertexSize;
	int indexTotalSize = (int)index.size() * (int)sizeof(vIndex);

	device->CreateVertexBuffer(vertexTotalSize, 0, fvf, D3DPOOL_MANAGED, &vertexBuffer, NULL);
	device->CreateIndexBuffer(indexTotalSize, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, NULL);

	t3dVertex* vertexData = nullptr;
	vertexBuffer->Lock(0, 0, (void**)&vertexData, 0);
	memcpy(vertexData, vertex.data(), vertexTotalSize);
	vertexBuffer->Unlock();

	vIndex* indexData = nullptr;
	indexBuffer->Lock(0, 0, (void**)&indexData, 0);
	memcpy(indexData, index.data(), indexTotalSize);
	indexBuffer->Unlock();
}
void Polygon::createPolygon(const std::vector<Texture3dVertex>& vertex, const std::vector<VertexIndex>& index, unsigned long& _triangleCount, bool notRHW)
{
	if (vertex.empty()) return;
	if (index.empty()) return;

	vertexSize = sizeof(t3dVertex);
	vertexCount = (unsigned long)vertex.size();
	triangleCount = _triangleCount;
	if (notRHW)
		fvf = Texture3dFVF;
	else
		fvf = Texture3dFVFRHW;

	int vertexTotalSize = vertexCount * vertexSize;
	int indexTotalSize = (int)index.size() * (int)sizeof(vIndex);

	device->CreateVertexBuffer(vertexTotalSize, 0, fvf, D3DPOOL_MANAGED, &vertexBuffer, NULL);
	device->CreateIndexBuffer(indexTotalSize, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, NULL);

	t3dVertex* vertexData = nullptr;
	vertexBuffer->Lock(0, 0, (void**)&vertexData, 0);
	memcpy(vertexData, vertex.data(), vertexTotalSize);
	vertexBuffer->Unlock();

	vIndex* indexData = nullptr;
	indexBuffer->Lock(0, 0, (void**)&indexData, 0);
	memcpy(indexData, index.data(), indexTotalSize);
	indexBuffer->Unlock();
}

void Polygon::createPolygon( std::vector<AdditionalTextureVertex>& vertex, const std::vector<VertexIndex>& index, bool rhw)
{
	if (vertex.empty()) return;
	if (index.empty()) return;

	vertexSize = sizeof(t3dVertex);
	vertexCount = (unsigned long)vertex.size();
	triangleCount = (unsigned long)index.size();
	if (rhw)
		fvf = Texture3dFVFRHW;
	else
		fvf = Texture3dFVF;

	int vertexTotalSize = vertexCount * vertexSize;
	int indexTotalSize = (int)index.size() * (int)sizeof(vIndex);

	std::vector<int> planeCount(vertex.size(), 0);

	for (auto& item : index)
	{
		Vector3 uVector = vertex[item._1].position - vertex[item._0].position;
		Vector3 vVector = vertex[item._2].position - vertex[item._0].position;
		Vector3 normal;
		D3DXVec3Cross(&normal, &uVector, &vVector);
		D3DXVec3Normalize(&normal, &normal);

		vertex[item._0].normalVector += normal;
		vertex[item._1].normalVector += normal;
		vertex[item._2].normalVector += normal;

		planeCount[item._0]++;
		planeCount[item._1]++;
		planeCount[item._2]++;
	}

	for (size_t i = 0; i < vertex.size(); i++)
	{
		vertex[i].normalVector /= planeCount[i];
	}


	device->CreateVertexBuffer(vertexTotalSize, 0, fvf, D3DPOOL_MANAGED, &vertexBuffer, NULL);
	device->CreateIndexBuffer(indexTotalSize, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, NULL);

	t3dVertex* vertexData = nullptr;
	vertexBuffer->Lock(0, 0, (void**)&vertexData, 0);
	memcpy(vertexData, vertex.data(), vertexTotalSize);
	vertexBuffer->Unlock();

	vIndex* indexData = nullptr;
	indexBuffer->Lock(0, 0, (void**)&indexData, 0);
	memcpy(indexData, index.data(), indexTotalSize);
	indexBuffer->Unlock();
}




Component* Polygon::clone(void)
{
	return new Polygon(*this);
}

void Polygon::render()
{
	device->SetFVF(fvf);
	if(indexBuffer)
		device->SetIndices(indexBuffer);
	if(worldMatrix)
		device->SetTransform(D3DTS_WORLD, worldMatrix);
	device->SetStreamSource(0, vertexBuffer, 0, vertexSize);
	if (indexBuffer)
		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, triangleCount);
	else
		device->DrawPrimitive(D3DPT_TRIANGLELIST,0,triangleCount);
}

Engine::Polygon* Polygon::create(LPDIRECT3DDEVICE9 _device)
{
	return new Polygon(_device);
}

void Polygon::release(void)
{
	if (isClone)
		return;
	vertexBuffer->Release();
	indexBuffer->Release();
}