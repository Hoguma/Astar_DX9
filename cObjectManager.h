#pragma once
#include "singleton.h"

enum ObjTag : char
{
	PLAYER,
	ENEMY,
	EFFECT,
	UI,
	END
};

class cObjectManager :
	public singleton<cObjectManager>
{
public:
	list<cObject*> objList[END];

	~cObjectManager() { Release(); }

	void Update();
	void Render();
	void Release();

	cObject* CreateObj(ObjTag tag, cObject* obj);

	cObject* GetPlayer()
	{
		return objList[PLAYER].front();
	}
};

#define OBJECT cObjectManager::Get()
#define ObjAdd(tag, obj) OBJECT->CreateObj(tag, new obj)