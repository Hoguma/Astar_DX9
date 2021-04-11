#pragma once
#include "singleton.h"
class cCameraManager :
	public singleton<cCameraManager>
{
public:
	Vec2 vCamPos = { 800, 450 };
	Vec2 vShakePos = { 0,0 };
	float fShScale = 0;
	float fShTimer = 0;
	float fScale = 1;
	bool isShake = false;

	Mat matView;

	void Update();
	void SetTransform();
	void CameraShake(float s, float t);
	void ZoomIn(Vec2 pos, float s);
	void ZoomOut();

	Mat GetMat()
	{
		Mat mat;
		D3DXMatrixInverse(&mat, 0, &matView);
		return mat;
	}
};

#define CAMERA cCameraManager::Get()