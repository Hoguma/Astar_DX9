#include "DXUT.h"
#include "cPlayer.h"

void cPlayer::Init()
{
	vPos.x = GAME->start->x * 100;
	vPos.y = GAME->start->y * 100;
}

void cPlayer::Update()
{
	if (GAME->GetClosedList().size() > 0)
	{
		auto iter = GAME->GetClosedList().front();
		nextPos = Vec2(iter->x * 100, iter->y * 100);
	}
	if (nextPos != vPos)
	{
		D3DXVec2Normalize(&vDir, &(nextPos - vPos));

		vPos.x = (int)(vPos.x + vDir.x * 2);
		vPos.y = (int)(vPos.y + vDir.y * 2);
	}
	else
	{
		vPos = nextPos;
		if (GAME->GetClosedList().size() > 0)
		{
			GAME->GetClosedList().pop_front();
		}
	}
}

void cPlayer::Render()
{
	RENDER->TileRender(RENDER->GetTexture("Player"), vPos);
	for (auto iter : GAME->GetClosedList())
	{
		RENDER->Render(to_string(iter->f), Vec2(iter->x * 100, iter->y * 100), 50);
	}

}

void cPlayer::Release()
{
}

void cPlayer::OnCollision(cCollider* col)
{
}
