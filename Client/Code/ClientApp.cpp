#include "pch.h"
#include "ClientApp.h"
#include "Player.h"
#include "MainScene.h"

Player* player = nullptr;
struct Vertex
{
    float x, y, z, rhw;      // 정점 위치
    DWORD color;        // 색상
};
#define D3DFVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

Vector3 position{ 0.0f, 0.0f, 0.0f };
Vector3 rotation{ 0.0f, 0.0f, 0.0f };

std::shared_ptr<Engine::InputManager> input = nullptr;
std::shared_ptr<Engine::TimeManager> Time = nullptr;

void init();
void checkInput();
void drawPolygon(LPDIRECT3DDEVICE9 _device);

ClientApp::ClientApp(void) : sceneManager(nullptr), device(nullptr)
{
}

ClientApp::~ClientApp(void)
{
}


HRESULT ClientApp::initiate(void)
{
    device = Engine::createDevice(instance, windowHandle);
    sceneManager = Engine::SceneManager::create(MainScene::create(device->getDevice()), L"MainScene");
    input = Engine::createInput(instance, windowHandle);
    Time = Engine::createTime();




    init();
    //player = new Player();
    //camera = Engine::Camera::create(windowHandle, device->getDevice());
    //player->camera = camera;
    //player->input = input;
    //player->Time = Time;
    rect = Engine::Polygon::create(device->getDevice());
    std::vector<Engine::SimpleVertex> vertices = {
        {{-1.0f, 0.0f, 0.5f}, D3DCOLOR_ARGB(255, 0, 0, 255)},
        {{0.0f, -1.0f, 0.5f}, D3DCOLOR_ARGB(255, 0, 0, 255)},
        {{-1.0f, -1.0f, 0.5f}, D3DCOLOR_ARGB(255, 0, 0, 255)},
         
        {{0.0f, -1.0f, 0.5f}, D3DCOLOR_ARGB(255, 0, 200, 0)},
        {{1.0f, 0.0f, 0.5f },D3DCOLOR_ARGB(255, 0, 200, 0)},
        {{1.0f, -1.0f, 0.5f}, D3DCOLOR_ARGB(255, 0, 200, 0)},
         
        {{-1.0f, 0.0f, 0.5f}, D3DCOLOR_ARGB(255, 255, 0, 0)},
        {{1.0f, 0.0f, 0.5f},D3DCOLOR_ARGB(255, 255, 0, 0)},
        {{0.0f, -1.0f, 0.5f}, D3DCOLOR_ARGB(255, 255, 0, 0)}
    };
    std::vector<Engine::vIndex> index = {
        {0,1,2},{3,4,5},{6,7,8}
    };
    rect->createPolygon(vertices, index, 3, false);
    return S_OK;
}

void ClientApp::frameCycle(void)
{

    checkInput();

    if (!sceneManager || !sceneManager->currentSceneExsist())
        return;

    sceneManager->update();
    sceneManager->lateUpdate();
    device->render([&](LPDIRECT3DDEVICE9 _device)->void
        {
            //test
            drawPolygon(_device);
            rect->render();
            //test

            sceneManager->render();
        });
    //sceneManager->fixedUpdate();
}


ClientApp* ClientApp::create(void)
{
	ClientApp* instance = new ClientApp();

	if (FAILED(instance->initiate()))
	{
		delete instance;
		return nullptr;
	}

	return instance;
}

void ClientApp::release(void)
{
    sceneManager->release();
    device->release();
}











void init()
{
    position = { 300.0f, 300.0f, 0.0f };
    rotation = { 0.0f, 0.0f, 0.0f };

}

void checkInput()
{
    Time->update();
    input->update();

    if (input->getButton(Engine::KeyType::W))
    {
        position.y -= Time->deltaTime() * 50.0f;
    }
    if (input->getButton(Engine::KeyType::S))
    {
        position.y += Time->deltaTime() * 50.0f;
    }
    if (input->getButton(Engine::KeyType::A))
    {
        position.x -= Time->deltaTime() * 50.0f;
    }
    if (input->getButton(Engine::KeyType::D))
    {
        position.x += Time->deltaTime() * 50.0f;
    }

    if (input->getButton(Engine::KeyType::Z))
    {
        rotation.x += Time->deltaTime() * 5.0f;
    }
    if (input->getButton(Engine::KeyType::X))
    {
        rotation.y += Time->deltaTime() * 5.0f;
    }
    if (input->getButton(Engine::KeyType::C))
    {
        rotation.z += Time->deltaTime() * 5.0f;
    }
    if (input->getButton(Engine::KeyType::V))
    {
        rotation = { 0.0f, 0.0f, 0.0f };
    }


}



void drawPolygon(LPDIRECT3DDEVICE9 _device)
{
    std::vector<Vertex> vertices = {
        {-1.0f, 0.0f, 0.5f, 1.0f, D3DCOLOR_ARGB(255, 0, 0, 255)},
        {0.0f, -1.0f, 0.5f, 1.0f,  D3DCOLOR_ARGB(255, 0, 0, 255)},
        {-1.0f, -1.0f, 0.5f, 1.0f, D3DCOLOR_ARGB(255, 0, 0, 255)},
    
        {0.0f, -1.0f, 0.5f, 1.0f, D3DCOLOR_ARGB(255, 0, 200, 0)},
        {1.0f, 0.0f, 0.5f, 1.0f, D3DCOLOR_ARGB(255, 0, 200, 0)},
        {1.0f, -1.0f, 0.5f, 1.0f, D3DCOLOR_ARGB(255, 0, 200, 0)},
    
        {-1.0f, 0.0f, 0.5f, 1.0f,D3DCOLOR_ARGB(255, 255, 0, 0)},
        {1.0f, 0.0f, 0.5f, 1.0f, D3DCOLOR_ARGB(255, 255, 0, 0)},
        {0.0f, -1.0f, 0.5f, 1.0f, D3DCOLOR_ARGB(255, 255, 0, 0)}
    };
    
    std::vector<Vertex> worldVertices = vertices;
    
    LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
    D3DXMATRIX worldMatrix, scaleMatrix, rotationMatrix, translationMatrix, tempMatrix;
    
    D3DXMatrixScaling(&scaleMatrix, 100.0f, 100.0f, 1.0f);
    D3DXMatrixRotationYawPitchRoll(&rotationMatrix, rotation.x, rotation.y, rotation.z);
    D3DXMatrixTranslation(&translationMatrix, position.x, position.y, 0.0f);

    worldMatrix = *D3DXMatrixMultiply(&tempMatrix, &scaleMatrix, &rotationMatrix);
    worldMatrix = *D3DXMatrixMultiply(&tempMatrix, &worldMatrix, &translationMatrix);


    for (int i = 0; i < 9; i++)
    {
        D3DXVECTOR3 worldPosition, localPosition = { vertices[i].x, vertices[i].y, vertices[i].z };
        D3DXVec3TransformCoord(&worldPosition, &localPosition, &worldMatrix);
    
        worldVertices[i].x = worldPosition.x;
        worldVertices[i].y = worldPosition.y;
        worldVertices[i].z = worldPosition.z;
    }
    
    _device->CreateVertexBuffer(9 * sizeof(Vertex), 0, D3DFVF_VERTEX, D3DPOOL_DEFAULT, &pVertexBuffer, NULL);

    Vertex* vertexData = nullptr;
    pVertexBuffer->Lock(0, 0, (void**)&vertexData, 0);
    memcpy(vertexData, worldVertices.data(), worldVertices.size() * sizeof(Vertex));
    pVertexBuffer->Unlock();
    
    _device->SetStreamSource(0, pVertexBuffer, 0, sizeof(Vertex));
    _device->SetFVF(D3DFVF_VERTEX);
    _device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 3);

    WORD Verticesindex[] = {
        0, 1,
        1, 2,
        2, 0,
    
        3, 4,
        4, 5,
        5, 3,
    
        6, 7
    };

    for (int i = 0; i < 9; i++)
    {
        worldVertices[i].color = D3DCOLOR_ARGB(255, 255, 255, 255);
    }
    VOID* pVoid;
    pVertexBuffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, worldVertices.data(), worldVertices.size() * sizeof(Vertex));
    pVertexBuffer->Unlock();

    LPDIRECT3DINDEXBUFFER9 indexBuffer;
    _device->CreateIndexBuffer(sizeof(Verticesindex), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer, NULL);

    indexBuffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, Verticesindex, sizeof(Verticesindex));
    indexBuffer->Unlock();

    _device->SetIndices(indexBuffer);
    _device->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, 9, 0, 7);
    pVertexBuffer->Release();
}


void drawTriangle(LPDIRECT3DDEVICE9 _device)
{
    std::vector<Vertex> vertices = {
        {0.0f, 0.0f, 0.5f, 1.0f, D3DCOLOR_ARGB(255, 255, 0, 0)},
        {1.0f, 0.0f, 0.5f, 1.0f, D3DCOLOR_ARGB(255, 255, 0, 0)},
        {0.0f, 1.0f, 0.5f, 1.0f, D3DCOLOR_ARGB(255, 255, 0, 0)}
    };

    Vertex worldVertices[3] = { vertices[0], vertices[1], vertices[2] };

    LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;

    D3DXMATRIX scaleMatrix, translationMatrix, worldMatrix;

    D3DXMatrixScaling(&scaleMatrix, 100.0f, 100.0f, 1.0f);
    D3DXMatrixTranslation(&translationMatrix, 100.0f, 100.0f, 0.0f);
    D3DXMatrixMultiply(&worldMatrix, &scaleMatrix, &translationMatrix);

    _device->CreateVertexBuffer(3 * sizeof(Vertex), 0, D3DFVF_VERTEX, D3DPOOL_DEFAULT, &pVertexBuffer, NULL);

    VOID* pVoid;
    pVertexBuffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, worldVertices, sizeof(worldVertices));
    pVertexBuffer->Unlock();

    for (int i = 0; i < 3; i++)
    {
        D3DXVECTOR3 localPosition = { vertices[i].x, vertices[i].y, vertices[i].z };
        D3DXVECTOR3 worldPosition = { worldVertices[i].x, worldVertices[i].y, worldVertices[i].z };
        D3DXVec3TransformCoord(&worldPosition, &localPosition, &worldMatrix);

        worldVertices[i].x = worldPosition.x;
        worldVertices[i].y = worldPosition.y;
        worldVertices[i].z = worldPosition.z;
    }

    _device->SetFVF(D3DFVF_VERTEX);
    _device->SetStreamSource(0, pVertexBuffer, 0, sizeof(Vertex));
    _device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

    Vertex lineVertices[] =
    {
        worldVertices[0], worldVertices[1],
        worldVertices[1], worldVertices[2],
        worldVertices[2], worldVertices[0] 
    };
    for (int i = 0; i < 6; i++)
    {
        lineVertices[i].color = D3DCOLOR_ARGB(255, 0, 0, 0);
    }

    pVertexBuffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, lineVertices, sizeof(lineVertices));
    pVertexBuffer->Unlock();

    _device->DrawPrimitive(D3DPT_LINELIST, 0, 3);
    pVertexBuffer->Release();
}

//
//void drawTriangle(LPDIRECT3DDEVICE9 _device)
//{
//    std::vector<Vertex> vertices = {
//        {0.0f, 0.0f, 0.5f, 1.0f, D3DCOLOR_ARGB(255, 255, 0, 0)},
//        {1.0f, 0.0f, 0.5f, 1.0f, D3DCOLOR_ARGB(255, 255, 0, 0)},
//        {0.0f, 1.0f, 0.5f, 1.0f, D3DCOLOR_ARGB(255, 255, 0, 0)}
//    };
//
//    Vertex worldVertices[3] = { vertices[0], vertices[1], vertices[2] };
//
//    LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
//
//    D3DXMATRIX scaleMatrix, translationMatrix, worldMatrix;
//
//    D3DXMatrixScaling(&scaleMatrix, 100.0f, 100.0f, 1.0f);
//    D3DXMatrixTranslation(&translationMatrix, 100.0f, 100.0f, 0.0f);
//    D3DXMatrixMultiply(&worldMatrix, &scaleMatrix, &translationMatrix);
//
//    _device->CreateVertexBuffer(3 * sizeof(Vertex), 0, D3DFVF_VERTEX, D3DPOOL_DEFAULT, &pVertexBuffer, NULL);
//
//    VOID* pVoid;
//    Vertex* vertexData;
//    pVertexBuffer->Lock(0, 0, (void**)&vertexData, 0);
//    for (size_t i = 0; i < vertices.size(); i++)
//    {
//        vertexData[i] = vertices[i];
//    }
//    pVertexBuffer->Unlock();
//
//    for (int i = 0; i < 3; i++)
//    {
//        D3DXVECTOR3 worldPosition;
//        D3DXVec3TransformCoord(&worldPosition, &D3DXVECTOR3{ vertices[i].x, vertices[i].y, vertices[i].z }, &worldMatrix);
//
//        worldVertices[i].x = worldPosition.x;
//        worldVertices[i].y = worldPosition.y;
//        worldVertices[i].z = worldPosition.z;
//    }
//
//    _device->SetFVF(D3DFVF_VERTEX);
//    _device->SetStreamSource(0, pVertexBuffer, 0, sizeof(Vertex));
//    _device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
//
//    Vertex lineVertices[] =
//    {
//        worldVertices[0], worldVertices[1],
//        worldVertices[1], worldVertices[2],
//        worldVertices[2], worldVertices[0] 
//    };
//    for (int i = 0; i < 6; i++)
//    {
//        lineVertices[i].color = D3DCOLOR_ARGB(255, 0, 0, 0);
//    }
//
//    pVertexBuffer->Lock(0, 0, (void**)&pVoid, 0);
//    memcpy(pVoid, lineVertices, sizeof(lineVertices));
//    pVertexBuffer->Unlock();
//
//    _device->DrawPrimitive(D3DPT_LINELIST, 0, 3);
//    pVertexBuffer->Release();
//}