#include "pch.h"
#include "MainScene.h"
#include "Player.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
	release();
}

void MainScene::release(void)
{
	player->release();
	object->release();
	testTile->release();
	terrain->release();

	delete player;
	delete object;
	delete testTile;
	delete terrain;

	player = nullptr;
	object = nullptr;
	testTile = nullptr;
	terrain = nullptr;
	//Engine::Scene::release();
}

void MainScene::start(void)
{
	Engine::Layer* playerLayer = Engine::Layer::create();
	layers[L"playerLayer"] = playerLayer;
	//playerLayer->addGameObject(Player::create());

	Engine::Scene::start();

	player = Player::create(device); 
	object = TestObject::create(device);
	skybox = Skybox::create(device);

	player->start();
	object->start();
	skybox->start();

	std::wstring filePath = L"D:\\Downloads\\nullTexture.jpg";
	testTile = Tile::create(device, filePath);
	testTile->transform()->scale *= 100.0f;
	testTile->transform()->scale.y= 1.0f;
	testTile->transform()->position = { 0.0f, 0.0f, 0.0f };
	testTile->transform()->rotation = { 0.0f, 0.0f, 0.0f };
	testTile->transform()->update();
	testTile->awake();

	skybox->awake();

	terrain = TestTerrain::create(device);

	object->linkTerrainVertex(terrain->linkNodeList());
	object->input = player->input;

	Engine::Text* newText = Engine::Text::create(device, L"", Vector2{ 100,100 });
	newText->setColor({1,1,1,1});
	debugTexts.push_back(newText);
	newText = Engine::Text::create(device, L"", Vector2{ 100,200 });
	newText->setColor({ 1,1,1,1 });
	debugTexts.push_back(newText);
}

void MainScene::awake(void)
{
	player->awake();
	object->awake();
	//Engine::Scene::awake();
	testTile->awake();
	terrain->awake();
	skybox->awake();
}

void MainScene::update(void)
{
	if (!player->terrainPos)
	{
		player->terrainPos = terrain->linkNodeList();
	}


	player->update();
	object->update();
	testTile->update();
	//Engine::Scene::update();
	terrain->update();
	skybox->setPosition(player->camera->transform()->position);
}

void MainScene::lateUpdate(void)
{
	player->lateUpdate();
	object->lateUpdate();
	testTile->lateUpdate();
	terrain->lateUpdate();
	//Engine::Scene::lateUpdate();
}

void MainScene::fixedUpdate(void)
{
	player->fixedUpdate();
	object->fixedUpdate();
	testTile->fixedUpdate();
	terrain->fixedUpdate();
	//Engine::Scene::fixedUpdate();
}

void MainScene::render(void)
{
	player->render();
	object->render();
	testTile->render();
	terrain->render();
	skybox->render();
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);

	device->SetTransform(D3DTS_WORLD, &matrix);
	Vector3 playerPosition = player->camera->transform()->position;
	std::wstring debugPositionText = std::to_wstring(playerPosition.x) + L":" + std::to_wstring(playerPosition.y) + L":" + std::to_wstring(playerPosition.z);
	debugTexts[0]->setText(debugPositionText);
	debugTexts[1]->setText(object->debugText);


	debugTexts[0]->render();
	debugTexts[1]->render();



	//Engine::Scene::render();
}

MainScene* MainScene::create(LPDIRECT3DDEVICE9 _device)
{
	MainScene* instance = new MainScene();
	instance->device = _device;
	return instance;
}



Engine::Matrix lookMatrix(const Vector3 at, const Vector3 eye, const Vector3 up)
{
	Engine::Matrix viewMatrix;
	Vector3 zVector = (at - eye).normalize();
	Vector3 xVector = up.cross(zVector).normalize();
	Vector3 yVector = zVector.cross(xVector);

	viewMatrix.m[0][0] = xVector.x;
	viewMatrix.m[1][0] = xVector.y;
	viewMatrix.m[2][0] = xVector.z;
	
	viewMatrix.m[0][1] = yVector.x;
	viewMatrix.m[1][1] = yVector.y;
	viewMatrix.m[2][1] = yVector.z;
	
	viewMatrix.m[0][2] = zVector.x;
	viewMatrix.m[1][2] = zVector.y;
	viewMatrix.m[2][2] = zVector.z;
	
	viewMatrix.m[3][0] = xVector.dot(eye) * -1.0f;
	viewMatrix.m[3][1] = yVector.dot(eye) * -1.0f;
	viewMatrix.m[3][2] = zVector.dot(eye) * -1.0f;

	viewMatrix.m[0][3] = 0;
	viewMatrix.m[1][3] = 0;
	viewMatrix.m[2][3] = 0;
	viewMatrix.m[3][3] = 1;

	return viewMatrix;
	//	설명
	//	이 함수의 반환 값은 pOut 매개 변수에 반환된 값과 동일합니다.이러한 방식으로 D3DXMatrixLookAtLH 함수를 다른 함수의 매개 변수로 사용할 수 있습니다.
	//	이 함수는 다음 수식을 사용하여 반환된 행렬을 계산합니다.
	// 
	//	zaxis = normal(At - Eye)
	//	xaxis = normal(cross(Up, zaxis))
	//	yaxis = cross(zaxis, xaxis)
	//
	//	xaxis.x           yaxis.x           zaxis.x          0
	//	xaxis.y           yaxis.y           zaxis.y          0
	//	xaxis.z           yaxis.z           zaxis.z          0
	//	- dot(xaxis, eye) - dot(yaxis, eye) - dot(zaxis, eye)  1
}

Engine::Matrix perspectiveMatrix(const Vector3 at, float fov, float aspect, float nearPlane, float farPlane)
{
	Engine::Matrix result;
	ZeroMemory(&result, sizeof(Engine::Matrix));
	
	float scale = 1.0f / tanf(fov / 2.0f);
	float middleCalculate = farPlane / (farPlane - nearPlane);
	result.m[0][0] = scale;
	result.m[1][1] = scale / aspect;
	result.m[2][2] = middleCalculate;
	result.m[3][3] = nearPlane * middleCalculate * -1.0f;
	result.m[2][3] = 1.0f;

	return result;
	// 설명
	// 이 함수의 반환 값은 pOut 매개 변수에 반환된 값과 동일합니다.이러한 방식으로 D3DXMatrixPerspectiveFovLH 함수를 다른 함수의 매개 변수로 사용할 수 있습니다.
	// 가로 세로 비율 축을 변경하려면 계산 수식을 사용합니다.fovy = 2 * math.atan(math.tan(fovy * 0.5) / aspect).또는 구조체에 X 및 Y 가로 세로 비율 변수를 추가하여 세로 뷰 공간의 크기를 조정합니다.fovy = 2 * math.atan(math.tan(fovy * 0.5) / aspectY), aspect = aspectX * aspect Y.
	//
	//	이 함수는 다음과 같이 반환된 행렬을 계산합니다.
	//  xScale     0          0               0
	//	0        yScale       0               0
	//	0          0       zf / (zf - zn)     1
	//	0          0 - zn * zf / (zf - zn)    0
	//	where:
	//  yScale = cot(fovY / 2)
	//	xScale = yScale / aspect ratio
}