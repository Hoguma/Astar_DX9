#include "DXUT.h"
#include "cGameManager.h"
#include "cPlayer.h"

cGameManager::~cGameManager()
{
	for (int i = 0; i < x; i++)
		delete[] Map[i];
	delete[] Map;

    for (auto iter : closedlist)
        SAFE_DELETE(iter);
    closedlist.clear();
    /*for (auto iter : deletelist)
        SAFE_DELETE(iter);
    deletelist.clear();*/
    openlist.clear();
}

void cGameManager::Init()
{
	cin >> x >> y;
	Map = new int*[x];
	for (int i = 0; i < x; i++)
		Map[i] = new int[y];

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			Map[i][j] = Road;
		}
	}
	for (int i = 0; i < x; i++)
	{
		Map[i][0] = Wall;
		Map[i][y - 1] = Wall;
	}

	for (int j = 0; j < y; j++)
	{
		Map[0][j] = Wall;
		Map[x - 1][j] = Wall;
	}
}

void cGameManager::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);
	Vec2 pos = Vec2(pt.x, pt.y);
	if (KeyDown('1'))
		SelectedTile = 1;
	if (KeyDown('2'))
		SelectedTile = 2;
	if (KeyDown('3'))
		SelectedTile = 3;
    if (isEdit)
    {
        if (KeyPress(VK_LBUTTON))
        {
            switch (SelectedTile)
            {
            case Wall:
                Map[Clamp((int)pos.x / 100, 0, x)][Clamp((int)pos.y / 100, 0, y)] = Wall;
                break;
            case Start:
                Map[Clamp((int)pos.x / 100, 0, x)][Clamp((int)pos.y / 100, 0, y)] = Start;
                break;
            case End:
                Map[Clamp((int)pos.x / 100, 0, x)][Clamp((int)pos.y / 100, 0, y)] = End;
                break;
            default:
                break;
            }
        }
        if (KeyPress(VK_RBUTTON))
        {
            Map[Clamp((int)pos.x / 100, 0, x)][Clamp((int)pos.y / 100, 0, y)] = Road;
        }
    }
    if (KeyDown(VK_SPACE))
    {
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                if (Map[i][j] == Start)
                {
                    start = new Node(i, j);
                    openlist.push_back(start);
                }
                if (Map[i][j] == End)
                    end = new Node(i, j);
            }
        }
        isEdit = false;
        Astar();
        ObjAdd(ObjTag::PLAYER, cPlayer());
    }
}

void cGameManager::Astar()
{
    if (isFind) return;
    Node* temp;
    int smaller = 10000;
    for (auto iter : openlist)
    {
        if (Map[iter->x][iter->y] == End)
        {
            closedlist.push_back(iter);
            isFind = true;
            return;
        }
        else if (iter->f < smaller)
        {
            smaller = iter->f;
            temp = iter;
        }
    }

    for (int i = temp->x -1; i < temp->x + 2; i++)
    {
        for (int j = temp->y -1; j < temp->y + 2; j++)
        {
            if (temp->x == i && temp->y == j) continue;

            auto it_open = find_if(openlist.begin(), openlist.end(), [&](Node* node)
                {
                    if (node->x == i && node->y == j)
                        return true;
                    else
                        return false;
                });

            auto it_close = find_if(closedlist.begin(), closedlist.end(), [&](Node* node)
                {
                    if (node->x == i && node->y == j)
                        return true;
                    else
                        return false;
                });

            if (it_open != openlist.end())
            {
                if ((*it_open)->g < temp->g + 1)
                {
                    if (abs(i) == abs(j)) (*it_open)->g = temp->g + 14;
                    else (*it_open)->g = temp->g + 10;
                    (*it_open)->f = (*it_open)->g + (abs(end->x - (*it_open)->x) + abs(end->y - (*it_open)->y)) * 10;
                }
            }
            else if (it_close != closedlist.end())
            {
                if ((*it_close)->g < temp->g + 1)
                {
                    if (abs(i) == abs(j)) (*it_close)->g = temp->g + 14;
                    else (*it_close)->g = temp->g + 10;
                    (*it_close)->f = (*it_close)->g + (abs(end->x - (*it_close)->x) + abs(end->y - (*it_close)->y)) * 10;
                }
            }
            else
            {
                if (Map[i][j] == Road)
                {
                    Node* child = new Node(i, j);
                    if (abs(i) == abs(j)) child->g = temp->g + 14;
                    else child->g = temp->g + 10;
                    child->f = child->g + (abs(end->x - child->x) + abs(end->y - child->y)) * 10;
                    openlist.push_back(child);
                }
                else if (Map[i][j] == End)
                {
                    Node* child = new Node(i, j);
                    if (abs(i) == abs(j)) child->g = temp->g + 14;
                    else child->g = temp->g + 10;
                    child->f = child->g;
                    openlist.push_back(child);
                }
            }
        }
    }

    openlist.remove_if([&](Node* node)
        {
            if (node->x == temp->x && node->y == temp->y)
            {
                return true;
            }
            else
            {
                return false;
            }
        });
    closedlist.push_back(temp);
    Astar();
}