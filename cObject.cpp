#include "DXUT.h"
#include "cObject.h"

void cObject::SetCollider(float rad, cObject* parent)
{
	collider = new cCollider();
	collider->fRadius = rad;
	collider->parent = parent;
	COLL->Register(collider);
}

void cObject::DestroyCollider()
{
	if (collider)
	{
		COLL->UnRegister(collider);
		collider->colEnterList.clear();
		SAFE_DELETE(collider);
	}
}
