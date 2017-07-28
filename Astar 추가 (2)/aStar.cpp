#include "stdafx.h"
#include "aStar.h"
#include "Scene.h"
#include "Rect.h"

aStar::aStar(LPDIRECT3DDEVICE9 device)
{
	this->device = device;
}


aStar::~aStar()
{
}

void aStar::Initialize()
{
	
	_aStarState = ASTAR_STATE_END;
	_selectedType = TILE_TYPE_EMPTY;
	_startPointSet = false;
	_endPointSet = false;
	device->SetRenderState(
		D3DRS_LIGHTING,	//라이팅모드	
		FALSE			//꺼버려라
	);

	//랜더링 파이프 라인중 라이팅을 설정 해야 vertice를 이용하여 도형의 색을 표현할수 있다
	//우리는 라이팅 설정을 하지 않았으므로 라이트를 꺼준다.
	rect = new Rect(device, { 0.0f,0.0f}, { WIDTH,HEIGHT });
	for (int i = 0; i < TILE_Y; i++) {
		for (int j = 0; j < TILE_X; j++) {
			_tile[i][j].type = TILE_TYPE_EMPTY;
			_tile[i][j].parent = NULL;
			_tile[i][j].F = BIGNUM;
			_tile[i][j].H = 0;
			_tile[i][j].i = i;
			_tile[i][j].j = j;
			_tile[i][j].vertices[0].pos
			//	= { -0.68f + 0.08f * j,0.5f,0};
			= { -0.68f + 0.08f*i ,1 - 0.1f*j,0 };
			_tile[i][j].vertices[1].pos =
				_tile[i][j].vertices[0].pos + D3DXVECTOR3(0.08f, 0, 0);
			_tile[i][j].vertices[2].pos =
				_tile[i][j].vertices[0].pos + D3DXVECTOR3(0, -0.1f , 0);
			_tile[i][j].vertices[3].pos =
				_tile[i][j].vertices[0].pos + D3DXVECTOR3(0.08f,-0.1f, 0);
			//_tile[i][j].vertices[4].pos =
				//_tile[i][j].vertices[0].pos + D3DXVECTOR3(0.08f, 0, 0);
			//_tile[i][j].vertices[5].pos =
				//_tile[i][j].vertices[1].pos + D3DXVECTOR3(0.08f, 0, 0);
			_tile[i][j].vertices[0].color = 0xFFFEFEEE;
			_tile[i][j].vertices[1].color = 0xFFFEFEEE;
			_tile[i][j].vertices[2].color = 0xFFFEFEEE;
			_tile[i][j].vertices[3].color = 0xFFFEFEEE;
			//_tile[i][j].vertices[4].color = 0xFFFF0000;
			//_tile[i][j].vertices[5].color = 0xFFFF0000;


		}
	}
}

void aStar::Destroy()
{
}

void aStar::Update()
{
	//아직 배치가 끝나지 않았다면
	if (_aStarState == ASTAR_STATE_END)
	{
		TileComposition();	//타일 배치
	}

	//시작지점 도착지점 설치 되어있고 , 스페이스 누르면타일 초기화
	if (Keyboard::GetInstance()->KeyDown(VK_SPACE)
		&& _startPointSet
		&& _endPointSet
		&& _aStarState == ASTAR_STATE_END) {
		TileInitializing();
	}

	//배치 중이거나, 발견 했거나, 길이 없다면 알고리즘 실행 X
	if (_aStarState == ASTAR_STATE_END ||
		_aStarState == ASTAR_STATE_FOUND ||
		_aStarState == ASTAR_STATE_NOWAY) return;

	AddOpenList();	//오픈리스트에 추가 후 G 값 계산
	CalculateH();
	CalculateF();
	AddCloseList();	//클로즈 리스트에 추가
	CheckArrive();	//도착 여부 체크
}

void aStar::Render()
{
	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);

	PrintText::GetInstance()->AddText(L"1 : EMPTY");
	PrintText::GetInstance()->AddText(L"2 : START");
	PrintText::GetInstance()->AddText(L"3 : END");
	PrintText::GetInstance()->AddText(L"4 : WALL");

	if (_aStarState == ASTAR_STATE_END)
		PrintText::GetInstance()->AddText(L"press Space to Start");
	else if (_aStarState == ASTAR_STATE_FOUND)
		PrintText::GetInstance()->AddText(L"way found");

	else if (_aStarState == ASTAR_STATE_NOWAY)
		PrintText::GetInstance()->AddText(L"no Way!!");

	else if (_aStarState == ASTAR_STATE_SEARCHING)
		PrintText::GetInstance()->AddText(L"now Searching...");

	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{

			device->SetFVF(MYVERTEX::FVF);

			device->DrawPrimitiveUP(
				D3DPT_TRIANGLESTRIP,
				2,
				_tile[i][j].vertices,
				sizeof(MYVERTEX)
			);

			rect->SetCoord({(float)(viewport.Width - (TILE_X + 1) * WIDTH + WIDTH*j),
				(float)(viewport.Height / 2 - (TILE_Y / 2) * HEIGHT + HEIGHT *i)
		});
			rect->Render();
			//F가 BIGNUM보다 작을 때만 (F/G/H)를 화면에 표시
			//PrintText 좌표 설정 문제로 주석처리
			/*if (_tile[i][j].F < BIGNUM)
			{
				wsprintf(_tile[i][j].str, L"%d", _tile[i][j].F);
				PrintText::GetInstance()->AddText(_tile[i][j].str);
				PrintText::GetInstance()->SetCoord({(LONG) rect->GetCoord().x, (LONG)rect->GetCoord().y });
				PrintText::GetInstance()->Render();
				wsprintf(_tile[i][j].str, L"%d", _tile[i][j].G);
				PrintText::GetInstance()->AddText(_tile[i][j].str);
				PrintText::GetInstance()->SetCoord({ (LONG)rect->GetCoord().x, (LONG)rect->GetCoord().y+5 });
				PrintText::GetInstance()->Render();
				wsprintf(_tile[i][j].str, L"%d", _tile[i][j].H);
				PrintText::GetInstance()->AddText(_tile[i][j].str);
				PrintText::GetInstance()->SetCoord({ (LONG)rect->GetCoord().x, (LONG)rect->GetCoord().y+10 });
				PrintText::GetInstance()->Render();
			}*/

			if (_tile[i][j].parent == nullptr) continue;
		}
	}

}

void aStar::TileComposition()
{
	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);
	//비어 있을때
	if (Keyboard::GetInstance()->KeyDown(VK_1)) { _selectedType = TILE_TYPE_EMPTY; _selectedTypeColor = 0xFFFEFEEE; }
	//스타트
	else if (Keyboard::GetInstance()->KeyDown(VK_2)) { _selectedType = TILE_TYPE_START; _selectedTypeColor = RGB(100, 255, 100);}
	//엔드
	else if (Keyboard::GetInstance()->KeyDown(VK_3)) { _selectedType = TILE_TYPE_END; _selectedTypeColor = RGB(255, 100, 100);}
	//벽일떄
	else if (Keyboard::GetInstance()->KeyDown(VK_4)) { _selectedType = TILE_TYPE_WALL; _selectedTypeColor = RGB(100, 100, 255); }


	if (Mouse::GetInstance()->ButtonDown(0))
	{
		for (int i = 0; i < TILE_Y; i++)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				/*float Xpos = (float)(viewport.Width - (TILE_X + 1) * WIDTH + WIDTH*j);
				float Ypos = (float)(viewport.Height / 2 - (TILE_Y / 2) * HEIGHT + HEIGHT *i);
				float MouseX =Mouse::GetInstance()->GetPosition().x;
				float MouseY = viewport.Height-Mouse::GetInstance()->GetPosition().y;*/
				//if (Xpos < MouseX && Xpos + WIDTH > MouseX &&  Ypos < MouseY && Ypos + WIDTH > MouseY)
				rect->SetCoord({ (float)(viewport.Width - (TILE_X + 1) * WIDTH + WIDTH*i),(float)(viewport.Height / 2 - (TILE_Y / 2) * HEIGHT + HEIGHT *j) });

				if(PtInRect(&rect->GetRect(), Mouse::GetInstance()->GetPosition()))
				{
					//시작지점 밑 끝지점 셋팅
					if (_tile[i][j].type == TILE_TYPE_START) _startPointSet = false;
					if (_tile[i][j].type == TILE_TYPE_END) _endPointSet = false;

					_tile[i][j].type = _selectedType;
					_tile[i][j].vertices[0].color = _selectedTypeColor;
					_tile[i][j].vertices[1].color = _selectedTypeColor;
					_tile[i][j].vertices[2].color = _selectedTypeColor;
					_tile[i][j].vertices[3].color = _selectedTypeColor;


					if (_selectedType == TILE_TYPE_START)
					{
						if (_startPointSet)
						{
							_tile[_startY][_startX].vertices[0].color= 0xFFFEFEEE;
							_tile[_startY][_startX].vertices[1].color = 0xFFFEFEEE;
							_tile[_startY][_startX].vertices[2].color = 0xFFFEFEEE;
							_tile[_startY][_startX].vertices[3].color = 0xFFFEFEEE;
							_tile[_startY][_startX].type = TILE_TYPE_EMPTY;
						}

						_startPointSet = true;
						_startX = j;
						_startY = i;
					}

					if (_selectedType == TILE_TYPE_END)
					{
						if (_endPointSet)
						{
							_tile[_endY][_endX].vertices[0].color = 0xFFFEFEEE;
							_tile[_endY][_endX].vertices[1].color = 0xFFFEFEEE;
							_tile[_endY][_endX].vertices[2].color = 0xFFFEFEEE;
							_tile[_endY][_endX].vertices[3].color = 0xFFFEFEEE;
							_tile[_endY][_endX].type = TILE_TYPE_EMPTY;
						}

						_endPointSet = true;
						_endX = j;
						_endY = i;
					}
				}
			}
		}
	}

}

void aStar::TileInitializing()
{
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			if (_tile[i][j].type == TILE_TYPE_EMPTY)                     //일반타일
			{
				_tile[i][j].walkable = true;
				_tile[i][j].liston = false;
			}
			else if (_tile[i][j].type == TILE_TYPE_WALL)                 //막힌타일
			{
				_tile[i][j].walkable = false;
				_tile[i][j].liston = false;
			}
			else if (_tile[i][j].type == TILE_TYPE_START)                //시작지점
			{
				_tile[i][j].walkable = true;
				_tile[i][j].liston = true;
				_closeList.push_back(&_tile[i][j]);
			}
			else if (_tile[i][j].type == TILE_TYPE_END)                  //도착지점
			{
				_endX = j;
				_endY = i;
				_tile[i][j].walkable = true;
				_tile[i][j].liston = false;
			}
		}
	}

	_aStarState = ASTAR_STATE_SEARCHING;
	_lastIndex = 0;
}

void aStar::AddOpenList()
{
	Ci = _closeList[_lastIndex]->i;                  //마지막으로 추가된 클로즈 리스트의 i
	Cj = _closeList[_lastIndex]->j;                  //마지막으로 추가된 클로즈 리스트의 j
	Cg = _closeList[_lastIndex]->G;                  //마지막으로 추가된 클로즈 리스트의 G

	if (Ci != 0)      //0번째 줄이 아니라면 상단 라인 계산
	{
		if (_tile[Ci - 1][Cj].walkable)     //상단 가운데 타일이 지나갈 수 있다면
		{
			if (!_tile[Ci - 1][Cj].liston)  //오픈리스트에 포함이 안 되어 있는 타일이라면
			{
				_tile[Ci - 1][Cj].liston = true;  //오픈리스트에 포함되었다
				_tile[_endY][_endX].vertices[0].color = 0xFF0FFFF0;
				_tile[_endY][_endX].vertices[1].color = 0xFF0FFFF0;
				_tile[_endY][_endX].vertices[2].color = 0xFF0FFFF0;
				_tile[_endY][_endX].vertices[3].color = 0xFF0FFFF0;
				_tile[Ci - 1][Cj].G = Cg + 10;//타일의 G값을 클로즈 리스트의 누적 G + 10
				_tile[Ci - 1][Cj].parent = _closeList[_lastIndex];  //타일의 부모를 클로즈 리스트의 마지막으로 추가된 타일로 설정
				_openList.push_back(&_tile[Ci - 1][Cj]);  //오픈리스트 벡터에 추가
			}//liton false
			else     //오픈리스트에 포함이 되어 있던 타일이라면
			{
				if (Cg + 10 < _tile[Ci - 1][Cj].G)//기존 G값보다 새로 계산한 G값이 작다면
				{
					_tile[Ci - 1][Cj].G = Cg + 10;  //G값 새롭게 계산
					_tile[Ci - 1][Cj].parent = _closeList[_lastIndex]; //타일의 부모를  클로즈 리스트의 마지막으로 추가된 타일로 재설정
				}
			}//liston true
		}//wakeable
		if (Cj != 0)      //좌상단 : 0번째 열이 아니라면
		{
			if (_tile[Ci - 1][Cj - 1].walkable && _tile[Ci - 1][Cj].walkable && _tile[Ci][Cj - 1].walkable)  //좌상단 타일의 왼쪽이나 아래에 벽이 없다면
			{
				if (!_tile[Ci - 1][Cj - 1].liston)
				{
					_tile[Ci - 1][Cj - 1].liston = true;
					_tile[_endY][_endX].vertices[0].color = 0xFF0FFFF0;
					_tile[_endY][_endX].vertices[1].color = 0xFF0FFFF0;
					_tile[_endY][_endX].vertices[2].color = 0xFF0FFFF0;
					_tile[_endY][_endX].vertices[3].color = 0xFF0FFFF0;
					_tile[Ci - 1][Cj - 1].G = Cg + 14;	//대각선이므로 G + 14
					_tile[Ci - 1][Cj - 1].parent = _closeList[_lastIndex];
					_openList.push_back(&_tile[Ci - 1][Cj - 1]);
				}//liston false
				else
				{
					if (Cg + 14 < _tile[Ci - 1][Cj - 1].G)
					{
						_tile[Ci - 1][Cj - 1].G = Cg + 14;
						_tile[Ci - 1][Cj - 1].parent = _closeList[_lastIndex];
					}
				}//liston true
			}//walkable
		}//cj != 0
		if (Cj != TILE_X - 1)   //우상단 : 마지막 열이 아니라면
		{
			if (_tile[Ci - 1][Cj + 1].walkable && _tile[Ci - 1][Cj].walkable && _tile[Ci][Cj + 1].walkable)  //우상단 타일의 왼쪽이나 아래에 벽이 없다면
			{
				if (!_tile[Ci - 1][Cj + 1].liston)
				{
					_tile[Ci - 1][Cj + 1].liston = true;
					_tile[_endY][_endX].vertices[0].color = 0xFF0FFFF0;
					_tile[_endY][_endX].vertices[1].color = 0xFF0FFFF0;
					_tile[_endY][_endX].vertices[2].color = 0xFF0FFFF0;
					_tile[_endY][_endX].vertices[3].color = 0xFF0FFFF0;
					_tile[Ci - 1][Cj + 1].G = Cg + 14;
					_tile[Ci - 1][Cj + 1].parent = _closeList[_lastIndex];
					_openList.push_back(&_tile[Ci - 1][Cj + 1]);
				}//liston else
				else
				{
					if (Cg + 14 < _tile[Ci - 1][Cj + 1].G)
					{
						_tile[Ci - 1][Cj + 1].G = Cg + 14;
						_tile[Ci - 1][Cj + 1].parent = _closeList[_lastIndex];
					}
				}//liston true
			}//walkable
		}//Cj != TILE_X -1
	}//Ci

	if (Cj != 0)      //좌측 : 0번째 열이 아니라면
	{
		if (_tile[Ci][Cj - 1].walkable) //좌측 타일이 이동가능하다면
		{
			if (!_tile[Ci][Cj - 1].liston)
			{
				_tile[Ci][Cj - 1].liston = true;
				_tile[_endY][_endX].vertices[0].color = 0xFF0FFFF0;
				_tile[_endY][_endX].vertices[1].color = 0xFF0FFFF0;
				_tile[_endY][_endX].vertices[2].color = 0xFF0FFFF0;
				_tile[_endY][_endX].vertices[3].color = 0xFF0FFFF0;
				_tile[Ci][Cj - 1].G = Cg + 10;
				_tile[Ci][Cj - 1].parent = _closeList[_lastIndex];
				_openList.push_back(&_tile[Ci][Cj - 1]);
			}//liston false
			else
			{
				if (Cg + 10 < _tile[Ci][Cj - 1].G)
				{
					_tile[Ci][Cj - 1].G = Cg + 10;
					_tile[Ci][Cj - 1].parent = _closeList[_lastIndex];
				}
			}//liston true
		}//walkable
	}//cj != 0

	if (Cj != TILE_X - 1) //우측 : 마지막 열이 아니라면
	{
		if (_tile[Ci][Cj + 1].walkable) //우측 타일이 이동가능하다면
		{
			if (!_tile[Ci][Cj + 1].liston)
			{
				_tile[Ci][Cj + 1].liston = true;
				_tile[_endY][_endX].vertices[0].color = 0xFF0FFFF0;
				_tile[_endY][_endX].vertices[1].color = 0xFF0FFFF0;
				_tile[_endY][_endX].vertices[2].color = 0xFF0FFFF0;
				_tile[_endY][_endX].vertices[3].color = 0xFF0FFFF0;
				_tile[Ci][Cj + 1].G = Cg + 10;
				_tile[Ci][Cj + 1].parent = _closeList[_lastIndex];
				_openList.push_back(&_tile[Ci][Cj + 1]);
			}//liston false
			else
			{
				if (Cg + 10 < _tile[Ci][Cj + 1].G)
				{
					_tile[Ci][Cj + 1].G = Cg + 10;
					_tile[Ci][Cj + 1].parent = _closeList[_lastIndex];
				}
			}//liston true
		}//walkable
	}//Cj != TILE_X -1

	if (Ci != TILE_Y - 1)   //마지막 행이 아니라면 하단 라인 계산
	{
		if (_tile[Ci + 1][Cj].walkable) //하단 가운데 타일이 이동가능하다면
		{
			if (!_tile[Ci + 1][Cj].liston)
			{
				_tile[Ci + 1][Cj].liston = true;
				_tile[_endY][_endX].vertices[0].color = 0xFF0FFFF0;
				_tile[_endY][_endX].vertices[1].color = 0xFF0FFFF0;
				_tile[_endY][_endX].vertices[2].color = 0xFF0FFFF0;
				_tile[_endY][_endX].vertices[3].color = 0xFF0FFFF0;
				_tile[Ci + 1][Cj].G = Cg + 10;
				_tile[Ci + 1][Cj].parent = _closeList[_lastIndex];
				_openList.push_back(&_tile[Ci + 1][Cj]);
			}//liston false
			else
			{
				if (Cg + 10 < _tile[Ci + 1][Cj].G)
				{
					_tile[Ci + 1][Cj].G = Cg + 10;
					_tile[Ci + 1][Cj].parent = _closeList[_lastIndex];
				}
			}//liston true
		}//Ci 1 = TILE_Y-1
		if (Cj != 0)            //좌하단 : 0번째 열이 아니라면
		{
			if (_tile[Ci + 1][Cj - 1].walkable && _tile[Ci + 1][Cj].walkable &&_tile[Ci][Cj - 1].walkable)   //좌하단 타일의 오른쪽이나 위에 벽이 없다면
			{
				if (!_tile[Ci + 1][Cj - 1].liston)
				{
					_tile[Ci + 1][Cj - 1].liston = true;
					_tile[_endY][_endX].vertices[0].color = 0xFF0FFFF0;
					_tile[_endY][_endX].vertices[1].color = 0xFF0FFFF0;
					_tile[_endY][_endX].vertices[2].color = 0xFF0FFFF0;
					_tile[_endY][_endX].vertices[3].color = 0xFF0FFFF0;
					_tile[Ci + 1][Cj - 1].G = Cg + 14;
					_tile[Ci + 1][Cj - 1].parent = _closeList[_lastIndex];
					_openList.push_back(&_tile[Ci + 1][Cj - 1]);
				}
				else//liston false
				{
					if (Cg + 14 < _tile[Ci + 1][Cj - 1].G)
					{
						_tile[Ci + 1][Cj - 1].G = Cg + 14;
						_tile[Ci + 1][Cj - 1].parent = _closeList[_lastIndex];
					}
				}//liston true
			}//cj !=0
		}
		if (Cj != TILE_X - 1)          //우하단 : 마지막 열이 아니라면
		{
			if (_tile[Ci + 1][Cj + 1].walkable && _tile[Ci + 1][Cj].walkable &&_tile[Ci][Cj + 1].walkable) //우하단 타일의 오른쪽이나 위가 이동가능하다면
			{
				if (!_tile[Ci + 1][Cj + 1].liston)
				{
					_tile[Ci + 1][Cj + 1].liston = true;
					_tile[_endY][_endX].vertices[0].color = 0xFF0FFFF0;
					_tile[_endY][_endX].vertices[1].color = 0xFF0FFFF0;
					_tile[_endY][_endX].vertices[2].color = 0xFF0FFFF0;
					_tile[_endY][_endX].vertices[3].color = 0xFF0FFFF0;
					_tile[Ci + 1][Cj + 1].G = Cg + 14;
					_tile[Ci + 1][Cj + 1].parent = _closeList[_lastIndex];
					_openList.push_back(&_tile[Ci + 1][Cj + 1]);
				}//liston false
				else
				{
					if (Cg + 14 < _tile[Ci + 1][Cj + 1].G)
					{
						_tile[Ci + 1][Cj + 1].G = Cg + 14;
						_tile[Ci + 1][Cj + 1].parent = _closeList[_lastIndex];
					}
				}//liston true
			}//walkable
		}//Cj ! = TILE_X -1
	}//Ci !=TILE_Y -1
}

void aStar::CalculateH()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		int vertical = (_endX - _openList[i]->j) * 10;     //가로 H값
		int horizontal = (_endY - _openList[i]->i) * 10;   //세로 H값

		if (vertical < 0) vertical *= -1;			//방향이 반대이면 음수 부여(절대값)
		if (horizontal < 0) horizontal *= -1;

		_openList[i]->H = vertical + horizontal;    //총 H값 = 가로H + 세로H
	}

}

void aStar::CalculateF()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		_openList[i]->F = _openList[i]->G + _openList[i]->H;               //F값 계산
	}
}


void aStar::AddCloseList()
{
	if (_openList.size() == 0)//검색했는데도 openlist의 사이즈가 0이라면 더이상 찾을 것이 없음
	{
		_aStarState = ASTAR_STATE_NOWAY; //경로가 없다
		return;                          //이하 작업 무시
	}

	int index = 0;                 //오픈리스트 중 가장 F가 작은 타일의 인덱스
	int lowest = BIGNUM;           //오픈리스트 중 가장 작은 F값
	for (int i = 0; i < _openList.size(); i++)
	{
		if (_openList[i]->F < lowest) //오픈리스트의 F가 가장 작은거보다 더 작다면
		{
			lowest = _openList[i]->F;   //lowest를 그 F로
			index = i;                  //index를 그 index로
		}
	}

	_openList[index]->vertices[0].color = RGB(180, 180, 255); //클로즈에 추가된 타일의 색상 : 연파랑
	_openList[index]->vertices[1].color = RGB(180, 180, 255); //클로즈에 추가된 타일의 색상 : 연파랑
	_openList[index]->vertices[2].color = RGB(180, 180, 255); //클로즈에 추가된 타일의 색상 : 연파랑
	_openList[index]->vertices[3].color = RGB(180, 180, 255);

	_closeList.push_back(_openList[index]);       //클로즈리스트에 추가
	_openList.erase(_openList.begin() + index);   //클로즈리스트에 추가된 타일은 오픈리스트에서 제외

	_lastIndex++;                                   //가장 나중에 추가된 클로즈의 인덱스
}

void aStar::CheckArrive()
{
	if (_closeList[_lastIndex]->i == _endY && _closeList[_lastIndex]->j == _endX) //클로즈리스트의 i j가 도착지점과 같다면
	{
		_aStarState = ASTAR_STATE_FOUND;                      //찾았다
		
		_closeList[_lastIndex]->vertices[0].color = 0xFF0000000;//도착지점 색상 빨강
		_closeList[_lastIndex]->vertices[1].color = 0xFF0000000;//도착지점 색상 빨강
		_closeList[_lastIndex]->vertices[2].color = 0xFF0000000;//도착지점 색상 빨강
		_closeList[_lastIndex]->vertices[3].color = 0xFF0000000;//도착지점 색상 빨강
		ShowWay(_closeList[_lastIndex]);                    //경로 보여준다
	}
}

void aStar::ShowWay(aStarTile * tile)
{
	if (!(tile->i == _endY && tile->j == _endX))	//도착지점이 아니라면
	{
		tile->vertices[0].color = RGB(255, 180, 180);				//색상 연분홍
		tile->vertices[1].color = RGB(255, 180, 180);				//색상 연분홍
		tile->vertices[2].color = RGB(255, 180, 180);				//색상 연분홍
		tile->vertices[3].color = RGB(255, 180, 180);				//색상 연분홍

	}
	tile = tile->parent;								//타일의 부모를 참조해서 showWay()함수에 다시 넣는다

	if (tile->parent == NULL)							//타일의 부모가 시작지점이면 그만 끝내라
		return;
	else
		ShowWay(tile);								//showWay() 다시 호출
}


