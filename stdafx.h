#pragma once
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <time.h>
#include <string>
#pragma comment (linker, "/entry:wWinMainCRTStartup /subsystem:console")

const int WINSIZEX = 1600;
const int WINSIZEY = 900;

#define gDevice DXUTGetD3D9Device()
#define Delta DXUTGetElapsedTime()

using namespace std;
using Vec2 = D3DXVECTOR2;
using Mat = D3DXMATRIX;
using Color = D3DXCOLOR;

namespace my
{
	static float GetLength(Vec2 v1, Vec2 v2)
	{
		return D3DXVec2Length(&(v1 - v2));
	}

	static float Vec2Rot(Vec2 v1)
	{
		return atan2(v1.y, v1.x);
	}

	static Vec2 Rot2Vec(float rot)
	{
		return Vec2(cos(rot), sin(rot));
	}

	template<typename T>
	static T Clamp(T t, T min, T max)
	{
		if (t < min) return min;
		else if (t > max) return max;
		else return t;
	}

	template<typename T>
	static void Lerp(T* t, T s, T e, float time)
	{
		*t = s + (e - s) * time;
	}
}

using namespace my;

#include "cCameraManager.h"
#include "cRenderManager.h"
#include "cObject.h"
#include "cCollider.h"
#include "cScene.h"
#include "cColliderManager.h"
#include "cObjectManager.h"
#include "cGameManager.h"
#include "cSceneManager.h"