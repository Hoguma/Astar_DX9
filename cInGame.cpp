#include "DXUT.h"
#include "cInGame.h"

void cInGame::Init()
{
}

void cInGame::Update()
{
}

void cInGame::Render()
{
	for (int i = 0; i < GAME->x; i++)
	{
		for (int j = 0; j < GAME->y; j++)
		{
			switch (GAME->Map[i][j])
			{
			case Road:
				RENDER->TileRender(RENDER->GetTexture("Road"), Vec2(i * 100, j * 100));
				break;
			case Wall:
				RENDER->TileRender(RENDER->GetTexture("Wall"), Vec2(i * 100, j * 100));
				break;
			case Start:
				RENDER->TileRender(RENDER->GetTexture("Start"), Vec2(i * 100, j * 100));
				break;
			case End:
				RENDER->TileRender(RENDER->GetTexture("Goal"), Vec2(i * 100, j * 100));
				break;
			default:
				break;
			}
		}
	}

	for (auto iter : GAME->closedlist)
	{
		RENDER->TileRender(RENDER->GetTexture("Start"), Vec2(iter->x * 100, iter->y * 100));
	}
} 

void cInGame::Release()
{
}
