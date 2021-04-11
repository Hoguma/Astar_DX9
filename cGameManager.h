#pragma once
#include "singleton.h"

enum Tile : char
{
	Road,
	Wall,
	Start,
	End
};

class Node {
public:
	int x, y; //index
	int f, g;

public:
	Node(int _x, int _y)
	{
		x = _x;
		y = _y;
		f = 0;
		g = 0;
	}
};

class cGameManager :
	public singleton<cGameManager>
{
public:
	int x, y;
	int** Map = nullptr;
	int SelectedTile = Road;
	list<Node*> openlist;
	list<Node*> closedlist;
	list<Node*> deletelist;

	Node* end;
	Node* start;

	bool isEdit = true;
	bool isFind = false;

	~cGameManager();
	void Init();
	void Update();
	void Astar();

	list<Node*>& GetClosedList() { return closedlist; }
};

#define GAME cGameManager::Get()