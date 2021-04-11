#include "DXUT.h"
#include "cSceneManager.h"

void cSceneManager::Update()
{
	if (next)
	{
		Lerp(&fAlpha, fAlpha, 255.f, 3 * Delta);
		if (fAlpha > 254)
		{
			if (now)
			{
				now->Release();
				OBJECT->Release();
			}
			next->Init();
			now = next;
			next = nullptr;
		}
	}
	if (now)
	{
		Lerp(&fAlpha, fAlpha, 0.f, 3 * Delta);
		if (fAlpha < 5)
		{
			now->Update();
			OBJECT->Update();
		}
	}
}

void cSceneManager::Render()
{
	if (now)
	{
		now->Render();
		OBJECT->Render();
	}
	if(tex) RENDER->UIRender(tex, Vec2(800, 450), 0, 1, D3DCOLOR_ARGB((int)fAlpha, 255, 255, 255));
}

void cSceneManager::Release()
{
	if (now)
	{
		now->Release();
		OBJECT->Release();
	}
	for (auto iter : sceneList)
	{
		iter.second->Release();
		SAFE_DELETE(iter.second);
	}
	sceneList.clear();
}

void cSceneManager::AddScene(string key, cScene* scene)
{
	sceneList.insert(make_pair(key, scene));
}

void cSceneManager::ChangeScene(string key)
{
	next = sceneList.find(key)->second;
}
