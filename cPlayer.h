#pragma once
#include "cObject.h"
class cPlayer :
	public cObject
{
public:
	Vec2 nextPos;

	// cObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void OnCollision(cCollider* col) override;
};

