#include "DXUT.h"
#include "cRenderManager.h"

cRenderManager::cRenderManager()
{
	D3DXCreateSprite(gDevice, &Sprite);
}

cRenderManager::~cRenderManager()
{
	for (auto iter : texList)
	{
		SAFE_RELEASE(iter.second->tex);
		SAFE_DELETE(iter.second);
	}
	texList.clear();
	SAFE_RELEASE(Sprite);
}

void cRenderManager::AddTexture(string key, string path, int count)
{
	LPDIRECT3DTEXTURE9 tex;
	D3DXIMAGE_INFO info;
	string _key, _path;
	if (count == 0)
	{
		_path = "./Resource/Texture/" + path + ".png";
		if (D3DXCreateTextureFromFileExA(gDevice, _path.c_str(), -2, -2, 0, 0,
			D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, -1, -1, 0, &info, nullptr, &tex) == S_OK)
		{
			texture* _tex = new texture(tex, info);
			texList.insert(make_pair(key, _tex));
		}
	}
	else
	{
		for (size_t i = 0; i < count; i++)
		{
			_key = key + to_string(i);
			_path = "./Resource/Texture/" + path + " ("+ to_string(i)+").png";
			if (D3DXCreateTextureFromFileExA(gDevice, _path.c_str(), -2, -2, 0, 0,
				D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, -1, -1, 0, &info, nullptr, &tex) == S_OK)
			{
				texture* _tex = new texture(tex, info);
				texList.insert(make_pair(_key, _tex));
			}
		}
	}
}

texture* cRenderManager::GetTexture(string key)
{
	return texList.find(key)->second;
}

vector<texture*> cRenderManager::VecTexture(string key, int count)
{
	vector<texture*> vec;
	string _key;
	for (size_t i = 0; i < count; i++)
	{
		_key = key + to_string(i);
		vec.push_back(GetTexture(_key));
	}
	return vec;
}

void cRenderManager::Render(texture* tex, Vec2 pos, float rot, float size, Color color)
{
	Mat mat;
	D3DXMatrixTransformation2D(&mat, &Vec2(tex->info.Width / 2, tex->info.Height / 2), 0, &Vec2(size, size),
		&Vec2(tex->info.Width / 2, tex->info.Height / 2), rot, &Vec2(pos.x - tex->info.Width / 2, pos.y - tex->info.Height / 2));
	Sprite->SetTransform(&mat);
	Sprite->Draw(tex->tex, nullptr, nullptr, nullptr, color);
}

void cRenderManager::TileRender(texture* tex, Vec2 pos)
{
	Mat mat;
	D3DXMatrixTransformation2D(&mat, nullptr, 0, &Vec2(1, 1), nullptr, 0, &pos);
	Sprite->SetTransform(&mat);
	Sprite->Draw(tex->tex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255,255,255, 255));
}

void cRenderManager::UIRender(texture* tex, Vec2 pos, float rot, float size, Color color)
{
	Mat mat;
	D3DXMatrixTransformation2D(&mat, &Vec2(tex->info.Width / 2, tex->info.Height / 2), 0, &Vec2(size, size),
		&Vec2(tex->info.Width / 2, tex->info.Height / 2), rot, &Vec2(pos.x - tex->info.Width / 2, pos.y - tex->info.Height / 2));
	mat *= CAMERA->GetMat();
	Sprite->SetTransform(&mat);
	Sprite->Draw(tex->tex, nullptr, nullptr, nullptr, color);
}

void cRenderManager::Render(string str, Vec2 pos, float size, Color color)
{
	D3DXCreateFontA(gDevice, size, 0, 0, 5, false, DEFAULT_CHARSET, 0, 0, 0, "System", &Font);
	Mat mat;
	D3DXMatrixTranslation(&mat, pos.x, pos.y, 0);
	Sprite->SetTransform(&mat);
	Font->DrawTextA(Sprite, str.c_str(), str.size(), nullptr, DT_CENTER, color);
}

void cRenderManager::UIRender(string str, Vec2 pos, float size, Color color)
{
	D3DXCreateFontA(gDevice, size, 0, 0, 5, false, DEFAULT_CHARSET, 0, 0, 0, "System", &Font);
	Mat mat;
	D3DXMatrixTranslation(&mat, pos.x, pos.y, 0);
	mat *= CAMERA->GetMat();
	Sprite->SetTransform(&mat);
	Font->DrawTextA(Sprite, str.c_str(), str.size(), nullptr, DT_CENTER, color);
}

void cRenderManager::Begin()
{
	Sprite->Begin(D3DXSPRITE_ALPHABLEND);
	gDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DX_FILTER_NONE);
	gDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DX_FILTER_NONE);
	gDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DX_FILTER_NONE);
}

void cRenderManager::End()
{
	Sprite->End();
}

void cRenderManager::Reset()
{
	Sprite->OnResetDevice();
}

void cRenderManager::Lost()
{
	Sprite->OnLostDevice();
}
