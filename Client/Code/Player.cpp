#include "pch.h"
#include "Player.h"
#include "Transform.h"

Player::Player() : camera(nullptr), input(nullptr), Time(nullptr), terrainPos(nullptr)
{
}

Player::~Player()
{
}

Player::Player(LPDIRECT3DDEVICE9& _device) : GameObject(_device),camera(nullptr),input(nullptr),Time(nullptr), terrainPos(nullptr)
{
}

Player::Player(Player& player) : GameObject(player), camera(player.camera), input(player.input), Time(player.Time)
{
}

void Player::start(void)
{
    camera = Engine::Camera::create(windowHandle, device);

    input = Engine::createInput(instance, windowHandle);
    //input->fixingMouse(true);
    Time = Engine::createTime();

}

void Player::update(void)
{
    Time->update();
    input->update();
    controlCamera();
    camera->update();
}

Engine::GameObject* Player::clone()
{
	return new Player(*this);
}

Player* Player::create(LPDIRECT3DDEVICE9& _device)
{
    Player* newPlayer = new Player();
    newPlayer->device = _device;
    newPlayer->start();
    return newPlayer;
}

bool Player::innerTriangle(const Vector3& currentPoint, const Vector3& vertice1, const Vector3& vertice2, const Vector3& vertice3)
{
    float size = 0.5f * std::abs(vertice1.x * (vertice2.z - vertice3.z) + vertice2.x * (vertice3.z - vertice1.z) + vertice3.x * (vertice1.z - vertice2.z));

    float alpha = 0.5f * std::abs(currentPoint.x * (vertice2.z - vertice3.z) + vertice2.x * (vertice3.z - currentPoint.z) + vertice3.x * (currentPoint.z - vertice2.z));
    float beta = 0.5f *  std::abs(currentPoint.x * (vertice3.z - vertice1.z) + vertice3.x * (vertice1.z - currentPoint.z) + vertice1.x * (currentPoint.z - vertice3.z));
    float gamma = 0.5f * std::abs(currentPoint.x * (vertice1.z - vertice2.z) + vertice1.x * (vertice2.z - currentPoint.z) + vertice2.x * (currentPoint.z - vertice1.z));

    alpha /= size;
    beta /= size;
    gamma /= size;

    return (alpha >= 0 && beta >= 0 && gamma >= 0) && std::abs(alpha + beta + gamma - 1.0f) < 0.00001f;
}

float Player::planeYCalculate(const Vector3& currentPoint, const Vector3& vertice1, const Vector3& vertice2, const Vector3& vertice3)
{
    D3DXPLANE plane;
    D3DXPlaneFromPoints(&plane, &vertice1, &vertice2, &vertice3);

    if (plane.b == 0.0f) // y축에 평행
        return currentPoint.y;

    return -(plane.a * currentPoint.x + plane.c * currentPoint.z + plane.d) / plane.b;
}

void Player::controlCamera(void)
{
    if (!input)
        return;
    if (input->getButton(Engine::KeyType::W))
    {
        camera->transform()->position.z -= Time->deltaTime() * 10.0f;
    }
    if (input->getButton(Engine::KeyType::S))
    {
        camera->transform()->position.z += Time->deltaTime() * 10.0f;
    }
    if (input->getButton(Engine::KeyType::A))
    {
        camera->transform()->position.x -= Time->deltaTime() * 10.0f;
    }
    if (input->getButton(Engine::KeyType::D))
    {
        camera->transform()->position.x += Time->deltaTime() * 10.0f;
    }

    //if (camera->transform()->position.x < 0 ||
    //    camera->transform()->position.x > terrainPos->back().x ||
    //    camera->transform()->position.z < 0 ||
    //    camera->transform()->position.z > terrainPos->back().z)
    //{
    //    //camera->transform()->position.y = 1.0f;
    //}
    //else
    //{
    //    float xGap = (*terrainPos)[1].x - (*terrainPos)[0].x;
    //    float zGap = (*terrainPos)[256].z - (*terrainPos)[0].z;

    //    int xIndex = (int)(camera->transform()->position.x / xGap);
    //    int zIndex = (int)(camera->transform()->position.z / zGap);

    //    if (xIndex >= 0 && zIndex >= 0)
    //    {
    //        Vector3 position = (*terrainPos)[zIndex * 256 + xIndex];

    //        if (innerTriangle(camera->transform()->position, (*terrainPos)[zIndex * 256 + xIndex], (*terrainPos)[(zIndex + 1) * 256 + (xIndex + 1)], (*terrainPos)[(zIndex + 1) * 256 + xIndex]))
    //        {
    //            float y = planeYCalculate(camera->transform()->position, (*terrainPos)[zIndex * 256 + xIndex], (*terrainPos)[(zIndex + 1) * 256 + (xIndex + 1)], (*terrainPos)[(zIndex + 1) * 256 + xIndex]);
    //            //camera->transform()->position.y = y * camera->transform()->scale.y + 1.0f;
    //            camera->transform()->position.y = y * 0.1f + 1.0f;
    //        }
    //        else
    //        {
    //            float y = planeYCalculate(camera->transform()->position, (*terrainPos)[zIndex * 256 + xIndex], (*terrainPos)[zIndex * 256 + (xIndex + 1)], (*terrainPos)[(zIndex + 1) * 256 + (xIndex + 1)]);
    //            //camera->transform()->position.y = y * camera->transform()->scale.y + 1.0f;
    //            camera->transform()->position.y = y * 0.1f + 1.0f;
    //        }





    //        //float y = ((*terrainPos)[zIndex * 256 + xIndex].y +
    //        //(*terrainPos)[zIndex * 256 + (xIndex + 1)].y +
    //        //(*terrainPos)[(zIndex + 1) * 256 + xIndex].y +
    //        //(*terrainPos)[(zIndex + 1) * 256 + (xIndex + 1)].y) / 4.0f;
    //        //
    //        //float yzMin, yxMin;
    //        //
    //        //camera->transform()->position.y = y * 0.1f + 1.0f;

    //        //float  y + index = (zGap / xGap)x + (xIndex * xGap) - (zIndex * zGap)
    //    }
    //    else
    //        int alarm = 0;


    //}


    if (input->getButton(Engine::KeyType::Space))
    {
        camera->transform()->position.y += Time->deltaTime() * 10.0f;
    }
    if (input->getButton(Engine::KeyType::C))
    {
        camera->transform()->position.y -= Time->deltaTime() * 10.0f;
    }


    if (input->getMouseButtonDown(Engine::MouseKey::RButton))
    {
        POINT screenMiddle{ 400,300 };
        ClientToScreen(windowHandle, &screenMiddle);
        SetCursorPos(screenMiddle.x, screenMiddle.y);
    }



    if (!input->getMouseButton(Engine::MouseKey::RButton))
    {
        POINT point = input->getMouseMovement();
        if (point.x != 0 || point.y != 0)
        {
            camera->transform()->rotation.x += (float)point.y * 0.1f;
            camera->transform()->rotation.y += (float)point.x * 0.1f;
            if (camera->transform()->rotation.x >= 85.0f)
                camera->transform()->rotation.x = 85.0f;
            else if (camera->transform()->rotation.x <= -85.0f)
                camera->transform()->rotation.x = -85.0f;
        }

    }



    //if (input->getButton(Engine::KeyType::X))
    //{
    //    camera->transform()->rotation.y += Time->deltaTime() * 50.0f;
    //    //if (camera->transform()->rotation.y >= 85.0f)
    //    //    camera->transform()->rotation.y = 85.0f;
    //}
    //if (input->getButton(Engine::KeyType::Z))
    //{
    //    camera->transform()->rotation.y -= Time->deltaTime() * 50.0f;
    //    //if (camera->transform()->rotation.y <= -85.0f)
    //    //    camera->transform()->rotation.y = -85.0f;
    //}
    //
    //if (input->getButton(Engine::KeyType::T))
    //{
    //    camera->transform()->rotation.x += Time->deltaTime() * 50.0f;
    //    if (camera->transform()->rotation.x >= 85.0f)
    //        camera->transform()->rotation.x = 85.0f;
    //}
    //if (input->getButton(Engine::KeyType::G))
    //{
    //    camera->transform()->rotation.x -= Time->deltaTime() * 50.0f;
    //    if (camera->transform()->rotation.x <= -85.0f)
    //        camera->transform()->rotation.x = -85.0f;
    //}
    //
    //if (input->getButton(Engine::KeyType::V))
    //{
    //    camera->transform()->rotation = { 0.0f, 0.0f, 0.0f };
    //}

    if (input->getMouseButtonDown(Engine::MouseKey::MButton))
    {
        camera->transform()->rotation = { 0.0f, 0.0f, 0.0f };
    }
    

}

