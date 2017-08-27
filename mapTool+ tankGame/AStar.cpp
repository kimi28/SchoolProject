#include "stdafx.h"
#include "AStar.h"
#include "Scene.h"
#include "Rect.h"



AStar::AStar(LPDIRECT3DDEVICE9 device)
	: device(device)
{
}


AStar::~AStar()
{
}

void AStar::Initialize()
{
	aStarState = ASTAR_STATE_END;
	selectedType = TILE_TYPE_EMPTY;
	startPointSet = false;
	endPointSet = false;

	device->SetRenderState(
		D3DRS_LIGHTING,
		FALSE
	);

	rect = new Rect(device, { 0.0f,0.0f }, { WIDTH, HEIGHT });
	for (int i = 0; i < TILE_Y; i++) {
		for (int j = 0; j < TILE_X; j++) {
			tile[i][j].type = TILE_TYPE_EMPTY;
			tile[i][j].parent = NULL;
			tile[i][j].F = BIGNUM;
			tile[i][j].H = 0;
			tile[i][j].i = i;
			tile[i][j].j = j;
			tile[i][j].vertices[0].pos = { -0.68f + 0.08f * i, 1.0f - 0.1f * j, 0 };
			tile[i][j].vertices[1].pos = tile[i][j].vertices[0].pos + D3DXVECTOR3(0.08f, 0, 0);
			tile[i][j].vertices[2].pos = tile[i][j].vertices[0].pos + D3DXVECTOR3(0, -0.1f, 0);
			tile[i][j].vertices[3].pos = tile[i][j].vertices[0].pos + D3DXVECTOR3(0.08f, -0.1f, 0);

			tile[i][j].vertices[0].color = 0xFFFEFEEE;
			tile[i][j].vertices[1].color = 0xFFFEFEEE;
			tile[i][j].vertices[2].color = 0xFFFEFEEE;
			tile[i][j].vertices[3].color = 0xFFFEFEEE;

		}
	}
}

void AStar::Destroy()
{
}

void AStar::Update()
{
	if (aStarState == ASTAR_STATE_END) {
		TileComposition();
	}
	if (Keyboard::GetInstance()->KeyDown(VK_SPACE)
		&& startPointSet
		&& endPointSet
		&& aStarState == ASTAR_STATE_END) {
		TileInitializing();
	}
	if (aStarState == ASTAR_STATE_END
		|| aStarState == ASTAR_STATE_FOUND
		|| aStarState == ASTAR_STATE_NOWAY) return;

	AddOpenList();
	CalculateH();
	CalculateF();
	AddCloseList();
	CheckArrive();
}

void AStar::Render()
{
	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);

	PrintText::GetInstance()->AddText(L"1: EMPTY");
	PrintText::GetInstance()->AddText(L"2: START");
	PrintText::GetInstance()->AddText(L"3: END");
	PrintText::GetInstance()->AddText(L"4: WALL");

	if (aStarState == ASTAR_STATE_END)
		PrintText::GetInstance()->AddText(L"press Space to Start");
	else if (aStarState == ASTAR_STATE_FOUND)
		PrintText::GetInstance()->AddText(L"way found");

	else if (aStarState == ASTAR_STATE_NOWAY)
		PrintText::GetInstance()->AddText(L"no Way!!");

	else if (aStarState == ASTAR_STATE_SEARCHING)
		PrintText::GetInstance()->AddText(L"now Searching...");

	for (int i = 0; i < TILE_Y; i++) {
		for (int j = 0; j < TILE_X; j++) {
			device->SetFVF(MYVERTEX::FVF);

			device->DrawPrimitiveUP(
				D3DPT_TRIANGLESTRIP,
				2,
				tile[i][j].vertices,
				sizeof(MYVERTEX)
			);

			rect->SetCoord({ (float)(viewport.Width - (TILE_X + 1) * WIDTH + WIDTH * j),
				(float)(viewport.Height / 2 - (TILE_Y / 2) * HEIGHT + HEIGHT * i)
			});
			rect->Render();

			if (tile[i][j].parent == nullptr) continue;
		}
	}
}

void AStar::TileComposition()
{
	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);

	//Rect* rect = new Rect(device, { 0,0 }, { WIDTH, HEIGHT });
	if (Keyboard::GetInstance()->KeyDown(VK_1)) {
		selectedType = TILE_TYPE_EMPTY;
		selectedTypeColor = 0xFFFEFEEE;
	}
	else if (Keyboard::GetInstance()->KeyDown(VK_2)) {
		selectedType = TILE_TYPE_START;
		selectedTypeColor = RGB(100, 255, 100);
	}
	else if (Keyboard::GetInstance()->KeyDown(VK_3)) {
		selectedType = TILE_TYPE_END;
		selectedTypeColor = RGB(255, 100, 100);
	}
	else if (Keyboard::GetInstance()->KeyDown(VK_4)) {
		selectedType = TILE_TYPE_WALL;
		selectedTypeColor = RGB(100, 100, 255);
	}

	if (Mouse::GetInstance()->ButtonDown(0)) {
		for (int i = 0; i < TILE_Y; i++) {
			for (int j = 0; j < TILE_X; j++) {
				rect->SetCoord({ (float)(viewport.Width - (TILE_X + 1)* WIDTH + WIDTH * i),
				(float)(viewport.Height / 2 - (TILE_Y / 2) * HEIGHT + HEIGHT * j) });

				if (PtInRect(&rect->GetRect(), Mouse::GetInstance()->GetPosition())) {
					if (tile[i][j].type == TILE_TYPE_START) startPointSet = false;
					if (tile[i][j].type == TILE_TYPE_END) endPointSet = false;

					tile[i][j].type = selectedType;
					tile[i][j].vertices[0].color = selectedTypeColor;
					tile[i][j].vertices[1].color = selectedTypeColor;
					tile[i][j].vertices[2].color = selectedTypeColor;
					tile[i][j].vertices[3].color = selectedTypeColor;

					if (selectedType == TILE_TYPE_START) {
						if (startPointSet) {
							tile[startX][startY].vertices[0].color = 0xFFFEFFEEE;
							tile[startX][startY].vertices[1].color = 0xFFFEFFEEE;
							tile[startX][startY].vertices[2].color = 0xFFFEFFEEE;
							tile[startX][startY].vertices[3].color = 0xFFFEFFEEE;
							tile[startX][startY].type = TILE_TYPE_EMPTY;
						}
						startPointSet = true;
						startX = i;
						startY = j;
					}

					if (selectedType == TILE_TYPE_END) {
						if (endPointSet) {
							tile[endX][endY].vertices[0].color = 0xFFFEFFEEE;
							tile[endX][endY].vertices[1].color = 0xFFFEFFEEE;
							tile[endX][endY].vertices[2].color = 0xFFFEFFEEE;
							tile[endX][endY].vertices[3].color = 0xFFFEFFEEE;
							tile[endX][endY].type = TILE_TYPE_EMPTY;
						}
						endPointSet = true;
						endX = i;
						endY = j;
					}
				}
			}
		}
	}
}

void AStar::TileInitializing()
{
	for (int i = 0; i < TILE_Y; i++) {
		for (int j = 0; j < TILE_X; j++) {
			if (tile[i][j].type == TILE_TYPE_EMPTY) {
				tile[i][j].walkable = true;
				tile[i][j].listOn = false;
			}
			else if (tile[i][j].type == TILE_TYPE_WALL) {
				tile[i][j].walkable = false;
				tile[i][j].listOn = false;
			}
			else if (tile[i][j].type == TILE_TYPE_START) {
				tile[i][j].walkable = true;
				tile[i][j].listOn = true;
				closeList.push_back(&tile[i][j]);
			}
			else if (tile[i][j].type == TILE_TYPE_END) {
				endX = j;
				endY = i;
				tile[i][j].walkable = true;
				tile[i][j].listOn = false;
			}
		}
	}
	aStarState = ASTAR_STATE_SEARCHING;
	lastIndex = 0;
}

void AStar::AddOpenList()
{
	Ci = closeList[lastIndex]->i;
	Cj = closeList[lastIndex]->j;
	Cg = closeList[lastIndex]->G;

	if (Ci != 0) {
		if (tile[Ci - 1][Cj].walkable) {
			if (!tile[Ci - 1][Cj].listOn) {
				tile[Ci - 1][Cj].listOn = true;;
				tile[endY][endX].vertices[0].color = 0xFF0FFFF0;
				tile[endY][endX].vertices[1].color = 0xFF0FFFF0;
				tile[endY][endX].vertices[2].color = 0xFF0FFFF0;
				tile[endY][endX].vertices[3].color = 0xFF0FFFF0;
				tile[Ci - 1][Cj].G = Cg + 10;
				tile[Ci - 1][Cj].parent = closeList[lastIndex];
				openList.push_back(&tile[Ci - 1][Cj]);
			}
			else
			{
				if (Cg + 10 < tile[Ci - 1][Cj].G) {
					tile[Ci - 1][Cj].G = Cg + 10;
					tile[Ci - 1][Cj].parent = closeList[lastIndex];
				}
			}
		}

		if (Cj != 0) {
			if (tile[Ci - 1][Cj - 1].walkable
				&& tile[Ci - 1][Cj].walkable
				&& tile[Ci][Cj - 1].walkable) {
				if (!tile[Ci - 1][Cj - 1].listOn) {
					tile[Ci - 1][Cj - 1].listOn = true;;
					tile[endY][endX].vertices[0].color = 0xFF0FFFF0;
					tile[endY][endX].vertices[1].color = 0xFF0FFFF0;
					tile[endY][endX].vertices[2].color = 0xFF0FFFF0;
					tile[endY][endX].vertices[3].color = 0xFF0FFFF0;
					tile[Ci - 1][Cj - 1].G = Cg + 14;
					tile[Ci - 1][Cj - 1].parent = closeList[lastIndex];
					openList.push_back(&tile[Ci - 1][Cj - 1]);
				}
				else
				{
					if (Cg + 14 < tile[Ci - 1][Cj - 1].G) {
						tile[Ci - 1][Cj - 1].G = Cg + 14;
						tile[Ci - 1][Cj - 1].parent = closeList[lastIndex];
					}
				}
			}
		}

		if (Cj != TILE_X - 1) {
			if (tile[Ci - 1][Cj + 1].walkable
				&& tile[Ci - 1][Cj].walkable
				&& tile[Ci][Cj + 1].walkable) {
				if (!tile[Ci - 1][Cj + 1].listOn) {
					tile[Ci - 1][Cj + 1].listOn = true;;
					tile[endY][endX].vertices[0].color = 0xFF0FFFF0;
					tile[endY][endX].vertices[1].color = 0xFF0FFFF0;
					tile[endY][endX].vertices[2].color = 0xFF0FFFF0;
					tile[endY][endX].vertices[3].color = 0xFF0FFFF0;
					tile[Ci - 1][Cj + 1].G = Cg + 14;
					tile[Ci - 1][Cj + 1].parent = closeList[lastIndex];
					openList.push_back(&tile[Ci - 1][Cj + 1]);
				}
				else
				{
					if (Cg + 14 < tile[Ci - 1][Cj + 1].G) {
						tile[Ci - 1][Cj + 1].G = Cg + 14;
						tile[Ci - 1][Cj + 1].parent = closeList[lastIndex];
					}
				}
			}
		}
	}

	if (Cj != 0) {
		if (tile[Ci][Cj - 1].walkable) {
			if (!tile[Ci][Cj - 1].listOn) {
				tile[Ci][Cj - 1].listOn = true;;
				tile[endY][endX].vertices[0].color = 0xFF0FFFF0;
				tile[endY][endX].vertices[1].color = 0xFF0FFFF0;
				tile[endY][endX].vertices[2].color = 0xFF0FFFF0;
				tile[endY][endX].vertices[3].color = 0xFF0FFFF0;
				tile[Ci][Cj - 1].G = Cg + 10;
				tile[Ci][Cj - 1].parent = closeList[lastIndex];
				openList.push_back(&tile[Ci][Cj - 1]);
			}
			else
			{
				if (Cg + 10 < tile[Ci][Cj - 1].G) {
					tile[Ci][Cj - 1].G = Cg + 10;
					tile[Ci][Cj - 1].parent = closeList[lastIndex];
				}
			}
		}
	}

	if (Cj != TILE_X - 1) {
		if (tile[Ci][Cj + 1].walkable) {
			if (!tile[Ci][Cj + 1].listOn) {
				tile[Ci][Cj + 1].listOn = true;;
				tile[endY][endX].vertices[0].color = 0xFF0FFFF0;
				tile[endY][endX].vertices[1].color = 0xFF0FFFF0;
				tile[endY][endX].vertices[2].color = 0xFF0FFFF0;
				tile[endY][endX].vertices[3].color = 0xFF0FFFF0;
				tile[Ci][Cj + 1].G = Cg + 10;
				tile[Ci][Cj + 1].parent = closeList[lastIndex];
				openList.push_back(&tile[Ci][Cj + 1]);
			}
			else
			{
				if (Cg + 10 < tile[Ci][Cj + 1].G) {
					tile[Ci][Cj + 1].G = Cg + 10;
					tile[Ci][Cj + 1].parent = closeList[lastIndex];
				}
			}
		}
	}

	if (Cj != TILE_Y - 1) {
		if (tile[Ci + 1][Cj].walkable) {
			if (!tile[Ci + 1][Cj].listOn) {
				tile[Ci + 1][Cj].listOn = true;;
				tile[endY][endX].vertices[0].color = 0xFF0FFFF0;
				tile[endY][endX].vertices[1].color = 0xFF0FFFF0;
				tile[endY][endX].vertices[2].color = 0xFF0FFFF0;
				tile[endY][endX].vertices[3].color = 0xFF0FFFF0;
				tile[Ci + 1][Cj].G = Cg + 10;
				tile[Ci + 1][Cj].parent = closeList[lastIndex];
				openList.push_back(&tile[Ci + 1][Cj]);
			}
			else
			{
				if (Cg + 10 < tile[Ci + 1][Cj].G) {
					tile[Ci + 1][Cj].G = Cg + 10;
					tile[Ci + 1][Cj].parent = closeList[lastIndex];
				}
			}
		}

		if (Cj != 0) {
			if (tile[Ci + 1][Cj - 1].walkable
				&& tile[Ci + 1][Cj].walkable
				&& tile[Ci][Cj - 1].walkable) {
				if (!tile[Ci + 1][Cj - 1].listOn) {
					tile[Ci + 1][Cj - 1].listOn = true;;
					tile[endY][endX].vertices[0].color = 0xFF0FFFF0;
					tile[endY][endX].vertices[1].color = 0xFF0FFFF0;
					tile[endY][endX].vertices[2].color = 0xFF0FFFF0;
					tile[endY][endX].vertices[3].color = 0xFF0FFFF0;
					tile[Ci + 1][Cj - 1].G = Cg + 14;
					tile[Ci + 1][Cj - 1].parent = closeList[lastIndex];
					openList.push_back(&tile[Ci + 1][Cj - 1]);
				}
				else
				{
					if (Cg + 14 < tile[Ci + 1][Cj - 1].G) {
						tile[Ci + 1][Cj - 1].G = Cg + 14;
						tile[Ci + 1][Cj - 1].parent = closeList[lastIndex];
					}
				}
			}
		}

		if (Cj != TILE_X - 1) {
			if (tile[Ci + 1][Cj + 1].walkable
				&& tile[Ci + 1][Cj].walkable
				&& tile[Ci][Cj + 1].walkable) {
				if (!tile[Ci + 1][Cj + 1].listOn) {
					tile[Ci + 1][Cj + 1].listOn = true;;
					tile[endY][endX].vertices[0].color = 0xFF0FFFF0;
					tile[endY][endX].vertices[1].color = 0xFF0FFFF0;
					tile[endY][endX].vertices[2].color = 0xFF0FFFF0;
					tile[endY][endX].vertices[3].color = 0xFF0FFFF0;
					tile[Ci + 1][Cj + 1].G = Cg + 14;
					tile[Ci + 1][Cj + 1].parent = closeList[lastIndex];
					openList.push_back(&tile[Ci + 1][Cj + 1]);
				}
				else
				{
					if (Cg + 14 < tile[Ci + 1][Cj + 1].G) {
						tile[Ci + 1][Cj + 1].G = Cg + 14;
						tile[Ci + 1][Cj + 1].parent = closeList[lastIndex];
					}
				}
			}
		}
	}
}

void AStar::CalculateH()
{
	for (int i = 0; i < openList.size(); i++) {
		int vertical = (endX - openList[i]->j) * 10;
		int horizontal = (endY - openList[i]->i) * 10;
		if (vertical < 0) vertical *= -1;
		if (horizontal < 0) horizontal *= -1;

		openList[i]->H = vertical + horizontal;
	}
}

void AStar::CalculateF()
{
	for (int i = 0; i < openList.size(); i++) {
		openList[i]->F = openList[i]->G + openList[i]->H;
	}
}

void AStar::AddCloseList()
{
	if (openList.size() == 0) {
		aStarState = ASTAR_STATE_NOWAY;
		return;
	}
	int index = 0;
	int lowest = BIGNUM;
	for (int i = 0; i < openList.size(); i++) {
		if (openList[i]->F < lowest) {
			lowest = openList[i]->F;
			index = i;
		}
	}
	openList[index]->vertices[0].color = RGB(180, 180, 255);
	openList[index]->vertices[1].color = RGB(180, 180, 255);
	openList[index]->vertices[2].color = RGB(180, 180, 255);
	openList[index]->vertices[3].color = RGB(180, 180, 255);

	closeList.push_back(openList[index]);
	openList.erase(openList.begin() + index);
	lastIndex++;
}

void AStar::CheckArrive()
{
	if (closeList[lastIndex]->i == endY &&
		closeList[lastIndex]->j == endX) {
		aStarState = ASTAR_STATE_FOUND;

		closeList[lastIndex]->vertices[0].color = 0xFFFF0000;
		closeList[lastIndex]->vertices[1].color = 0xFFFF0000;
		closeList[lastIndex]->vertices[2].color = 0xFFFF0000;
		closeList[lastIndex]->vertices[3].color = 0xFFFF0000;
		ShowWay(closeList[lastIndex]);
	}
}

void AStar::ShowWay(aStarTile * tile)
{
	if (tile->i == endY && tile->j == endX) {
		tile->vertices[0].color = RGB(255, 0, 180);
		tile->vertices[1].color = RGB(255, 0, 180);
		tile->vertices[2].color = RGB(255, 0, 180);
		tile->vertices[3].color = RGB(255, 0, 180);
	}
	tile = tile->parent;
	if (tile->parent == NULL) {
		return;
	}
	else {
		ShowWay(tile);
	}
}
