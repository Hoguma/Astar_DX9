#pragma once
class cCollider;
class cObject
{
public:
	Vec2 vPos;
	Vec2 vSpeed;
	Vec2 vDir;
	float fSpeed;
	float fSize = 1;
	float fRot = 0;

	bool isDestroy = false;

	int tag;

	texture* pTex;

	cCollider* collider;

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
	virtual void OnCollision(cCollider* col) = 0;

	void SetCollider(float rad, cObject* parent);
	void DestroyCollider();
};

