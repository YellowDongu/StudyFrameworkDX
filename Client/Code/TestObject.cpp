#include "pch.h"
#include "TestObject.h"
#include "Transform.h"
#include "Texture.h"
#include "Polygon.h"



TestObject::TestObject(void) : texture(nullptr), transformComponent(nullptr), polygon(nullptr), terrainPos(nullptr), isMoving(false), destination{0.0f, 0.0f, 0.0f}
{
}

TestObject::~TestObject(void)
{
	
}

void TestObject::start(void)
{
	texture = new Engine::Texture(device);
	if (FAILED(texture->loadTexture(L"D:\\Downloads\\1000170385807_i1_1200.jpg")))
	{
		delete texture;
		texture = nullptr;
	}
	transformComponent = Engine::Transform::create(device);
	transformComponent->position = { 0.0f, 0.0f , 0.0f };
	transformComponent->scale = { 10.0f, 10.0f , 10.0f };
	polygon = Engine::Polygon::create(device);
	std::vector<Engine::tVertex> vertex = {
	{{ -1.0f,  1.0f, 0.0f },{ 0.f, 0.f }},
	{{  1.0f,  1.0f, 0.0f },{ 1.f, 0.f }},
	{{  1.0f, -1.0f, 0.0f },{ 1.f, 1.f }},
	{{ -1.0f, -1.0f, 0.0f },{ 0.f, 1.f }}
	};
	std::vector<Engine::vIndex> index = {
		{0,2,1},
		{0,3,2}
	};
	unsigned long triangle = index.size();

	polygon->createPolygon(vertex, index);
}

void TestObject::update(void)
{
	{
		Vector3 rayDirection = { 0,0,0 };

		Engine::Matrix viewMatrix;
		device->GetTransform(D3DTS_VIEW, &viewMatrix);
		D3DXMatrixInverse(&viewMatrix, 0, &viewMatrix);


		Vector3 rayPosition = { viewMatrix._41,viewMatrix._42,viewMatrix._43 };
		Vector3 rayPosition2 = rayPosition;
		input->raycastWorldSpace(device, rayPosition, rayDirection);

		float u = 0.0f, v = 0.0f, temp = 0.0f;

		Vector3 vertex1 = { 0.0f, 0.0f, 0.0f };
		Vector3 vertex2 = { 1000.0f, 0.0f, 0.0f };
		Vector3 vertex3 = { 0.0f, 0.0f, 1000.0f };

		if (D3DXIntersectTri(&vertex1, &vertex2, &vertex3, &rayPosition, &rayDirection, &u, &v, &temp))
		{
			destination = vertex1 + (vertex2 - vertex1) * u + (vertex3 - vertex1) * v;
			isMoving = true;
			Vector3 targetDestinationOther = rayPosition + (rayDirection * temp);
			int alarm = 0;

			debugText = std::to_wstring(targetDestinationOther.x) + L":" + std::to_wstring(targetDestinationOther.y) + L":" + std::to_wstring(targetDestinationOther.z);
			return;
		}
		else
		{
			debugText = L"0:0:0";
		}
	}



	if (input->getMouseButton(Engine::MouseKey::LButton))
	{
		Vector3 rayDirection = {0,0,0};

		Engine::Matrix viewMatrix;
		device->GetTransform(D3DTS_VIEW, &viewMatrix);
		D3DXMatrixInverse(&viewMatrix, 0, &viewMatrix);

		Vector3 rayPosition = { viewMatrix._41,viewMatrix._42,viewMatrix._43 };
		Vector3 rayPosition2 = rayPosition;

		input->raycastWorldSpace(device, rayPosition, rayDirection);
		Engine::Matrix test;
		D3DXMatrixScaling(&test, 1.0f, 0.1f, 1.0f);
		for (int y = 0; y < 255; y++)
		{
			for (int x = 0; x < 255; x++)
			{
				float u = 0.0f, v = 0.0f, temp = 0.0f;
				Vector3 vertex1 = (*terrainPos)[y * 256 + x];
				Vector3 vertex2 = (*terrainPos)[y * 256 + (x + 1)];
				Vector3 vertex3 = (*terrainPos)[(y + 1) * 256 + (x + 1)];
				Vector3 vertex4 = (*terrainPos)[(y + 1) * 256 + x];
				D3DXVec3TransformCoord(&vertex1, &vertex1, &test);
				D3DXVec3TransformCoord(&vertex2, &vertex2, &test);
				D3DXVec3TransformCoord(&vertex3, &vertex3, &test);
				D3DXVec3TransformCoord(&vertex4, &vertex4, &test);





				if (D3DXIntersectTri(&vertex1, &vertex2, &vertex3, &rayPosition, &rayDirection, &u, &v, &temp))
				{	
					destination = vertex1 + (vertex2 - vertex1) * u + (vertex3 - vertex1) * v;
					isMoving = true;
					Vector3 targetDestination = vertex1 + (vertex2 - vertex1) * u + (vertex3 - vertex1) * v;
					Vector3 targetDestinationOther = rayPosition + (rayDirection * temp);
					int alarm = 0;

					return;
				}

				if (D3DXIntersectTri(&vertex1, &vertex4, &vertex3, &rayPosition, &rayDirection, &u, &v, &temp))
				{
					
					destination = vertex1 + (vertex4 - vertex1) * u + (vertex3 - vertex1) * v;
					isMoving = true;
					Vector3 targetDestination = vertex1 + (vertex2 - vertex1) * u + (vertex3 - vertex1) * v;
					Vector3 targetDestinationOther = rayPosition + (rayDirection * temp);
					int alarm = 0;
					return;
				}

			}
		}
	}





	if (isMoving)
	{
		Vector3 direction = destination - transformComponent->position;
		if (direction.magnitude() < 1.0f)
			isMoving = false;
		else
		{
			//direction.normalize();
			
			transformComponent->position = destination;

			if (terrainPos)
			{
				if (transformComponent->position.x < 0 ||
					transformComponent->position.x > terrainPos->back().x ||
					transformComponent->position.z < 0 ||
					transformComponent->position.z > terrainPos->back().z)
				{
					int alarm = 0;
				}
				else
				{
					float xGap = (*terrainPos)[1].x - (*terrainPos)[0].x;
					float zGap = (*terrainPos)[256].z - (*terrainPos)[0].z;

					int xIndex = (int)(transformComponent->position.x / xGap);
					int zIndex = (int)(transformComponent->position.z / zGap);

					if (xIndex >= 0 && zIndex >= 0)
					{
						Vector3 position = (*terrainPos)[zIndex * 256 + xIndex];

						if (innerTriangle(transformComponent->position, (*terrainPos)[zIndex * 256 + xIndex], (*terrainPos)[(zIndex + 1) * 256 + (xIndex + 1)], (*terrainPos)[(zIndex + 1) * 256 + xIndex]))
						{
							float y = planeYCalculate(transformComponent->position, (*terrainPos)[zIndex * 256 + xIndex], (*terrainPos)[(zIndex + 1) * 256 + (xIndex + 1)], (*terrainPos)[(zIndex + 1) * 256 + xIndex]);
							//camera->transform()->position.y = y * camera->transform()->scale.y + 1.0f;
							transformComponent->position.y = y * 0.1f + 1.0f;
						}
						else
						{
							float y = planeYCalculate(transformComponent->position, (*terrainPos)[zIndex * 256 + xIndex], (*terrainPos)[zIndex * 256 + (xIndex + 1)], (*terrainPos)[(zIndex + 1) * 256 + (xIndex + 1)]);
							//camera->transform()->position.y = y * camera->transform()->scale.y + 1.0f;
							transformComponent->position.y = y * 0.1f + 1.0f;
						}
					}
					else
						int alarm = 0;


				}
			}
			isMoving = false;
		}
	}




}

void TestObject::render(void)
{
	transformComponent->update();
	transformComponent->applyWorldMatrix();
	texture->setTexture(0);
	polygon->render();
}

TestObject* TestObject::create(LPDIRECT3DDEVICE9 _device)
{
	TestObject* newObject = new TestObject();
	newObject->device = _device;
	newObject->start();
	return newObject;
}

Engine::GameObject* TestObject::clone(void)
{
	return new TestObject(*this);
}

bool TestObject::innerTriangle(const Vector3& currentPoint, const Vector3& vertice1, const Vector3& vertice2, const Vector3& vertice3)
{
	float size = 0.5f * std::abs(vertice1.x * (vertice2.z - vertice3.z) + vertice2.x * (vertice3.z - vertice1.z) + vertice3.x * (vertice1.z - vertice2.z));

	float alpha = 0.5f * std::abs(currentPoint.x * (vertice2.z - vertice3.z) + vertice2.x * (vertice3.z - currentPoint.z) + vertice3.x * (currentPoint.z - vertice2.z));
	float beta = 0.5f * std::abs(currentPoint.x * (vertice3.z - vertice1.z) + vertice3.x * (vertice1.z - currentPoint.z) + vertice1.x * (currentPoint.z - vertice3.z));
	float gamma = 0.5f * std::abs(currentPoint.x * (vertice1.z - vertice2.z) + vertice1.x * (vertice2.z - currentPoint.z) + vertice2.x * (currentPoint.z - vertice1.z));

	alpha /= size;
	beta /= size;
	gamma /= size;

	return (alpha >= 0 && beta >= 0 && gamma >= 0) && std::abs(alpha + beta + gamma - 1.0f) < 0.00001f;
}

float TestObject::planeYCalculate(const Vector3& currentPoint, const Vector3& vertice1, const Vector3& vertice2, const Vector3& vertice3)
{
	D3DXPLANE plane;
	D3DXPlaneFromPoints(&plane, &vertice1, &vertice2, &vertice3);

	if (plane.b == 0.0f) // y축에 평행
		return currentPoint.y;

	return -(plane.a * currentPoint.x + plane.c * currentPoint.z + plane.d) / plane.b;
}

