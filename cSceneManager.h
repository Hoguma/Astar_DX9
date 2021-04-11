#pragma once
#include "singleton.h"
class cSceneManager :
	public singleton<cSceneManager>
{
public:
	map<string, cScene*> sceneList;
	cScene* now;
	cScene* next;
	float fAlpha = 255;
	texture* tex = nullptr;

	~cSceneManager() { Release(); }
	void Update();
	void Render();
	void Release();

	void AddScene(string key, cScene* scene);
	void ChangeScene(string key);
};

#define SCENE cSceneManager::Get()