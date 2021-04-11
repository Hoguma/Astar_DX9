#include "DXUT.h"
#include "cMain.h"
#include "cInGame.h"

void cMain::Init()
{
	Add();
	GAME->Init();
	SCENE->AddScene("InGame", new cInGame());
	SCENE->ChangeScene("InGame");
}

void cMain::Update()
{
	SCENE->Update();
	GAME->Update();
	COLL->Update();
	CAMERA->Update();
}

void cMain::Render()
{
	RENDER->Begin();
	CAMERA->SetTransform();
	SCENE->Render();
	RENDER->End();
}

void cMain::Release()
{
	cCameraManager::Del();
	cRenderManager::Del();
	cColliderManager::Del();
	cSceneManager::Del();
	cObjectManager::Del();
	cGameManager::Del();
}

void cMain::Reset()
{
	RENDER->Reset();
}

void cMain::Lost()
{
	RENDER->Lost();
}

void cMain::Add()
{
	RENDER->AddTexture("Road", "Road");
	RENDER->AddTexture("Wall", "Wall");
	RENDER->AddTexture("Goal", "Goal");
	RENDER->AddTexture("Start", "Start");
	RENDER->AddTexture("Player", "Player");
}
