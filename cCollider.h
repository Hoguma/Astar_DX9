#pragma once
class cCollider
{
public:
	cObject* parent;
	float fRadius;
	set<cObject*> colEnterList;

	void OnCollision(cCollider* col);
};

