#include "DXUT.h"
#include "cColliderManager.h"

void cColliderManager::Update()
{
	if (colList.size() < 2) return;
	for (auto iter1 : colList)
	{
		for (auto iter2 : colList)
		{
			if (iter1 == iter2) continue;
			if (iter1->parent->isDestroy && iter2->parent->isDestroy) continue;

			float length = GetLength(iter1->parent->vPos, iter2->parent->vPos);
			if (length < iter1->fRadius + iter2->fRadius)
			{
				iter1->OnCollision(iter2);
				if (auto col = iter1->colEnterList.find(iter2->parent); col == iter1->colEnterList.end())
					iter1->colEnterList.insert(iter2->parent);
			}
		}
	}
}

void cColliderManager::Release()
{
	for (auto iter : colList)
	{
		SAFE_DELETE(iter);
	}
	colList.clear();
}

void cColliderManager::Register(cCollider* col)
{
	colList.push_back(col);
}

void cColliderManager::UnRegister(cCollider* col)
{
	colList.remove(col);
}
