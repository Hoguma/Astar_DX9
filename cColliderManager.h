#pragma once
#include "singleton.h"
class cColliderManager :
	public singleton<cColliderManager>
{
public:
	list<cCollider*> colList;

	void Update();
	void Release();
	void Register(cCollider* col);
	void UnRegister(cCollider* col);
};

#define COLL cColliderManager::Get()