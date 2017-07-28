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
		D3DRS_LIGHTING,	//�����ø��	
		FALSE			//��������
	);

	//������ ������ ������ �������� ���� �ؾ� vertice�� �̿��Ͽ� ������ ���� ǥ���Ҽ� �ִ�
	//�츮�� ������ ������ ���� �ʾ����Ƿ� ����Ʈ�� ���ش�.
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
	//���� ��ġ�� ������ �ʾҴٸ�
	if (_aStarState == ASTAR_STATE_END)
	{
		TileComposition();	//Ÿ�� ��ġ
	}

	//�������� �������� ��ġ �Ǿ��ְ� , �����̽� ������Ÿ�� �ʱ�ȭ
	if (Keyboard::GetInstance()->KeyDown(VK_SPACE)
		&& _startPointSet
		&& _endPointSet
		&& _aStarState == ASTAR_STATE_END) {
		TileInitializing();
	}

	//��ġ ���̰ų�, �߰� �߰ų�, ���� ���ٸ� �˰��� ���� X
	if (_aStarState == ASTAR_STATE_END ||
		_aStarState == ASTAR_STATE_FOUND ||
		_aStarState == ASTAR_STATE_NOWAY) return;

	AddOpenList();	//���¸���Ʈ�� �߰� �� G �� ���
	CalculateH();
	CalculateF();
	AddCloseList();	//Ŭ���� ����Ʈ�� �߰�
	CheckArrive();	//���� ���� üũ
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
			//F�� BIGNUM���� ���� ���� (F/G/H)�� ȭ�鿡 ǥ��
			//PrintText ��ǥ ���� ������ �ּ�ó��
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
	//��� ������
	if (Keyboard::GetInstance()->KeyDown(VK_1)) { _selectedType = TILE_TYPE_EMPTY; _selectedTypeColor = 0xFFFEFEEE; }
	//��ŸƮ
	else if (Keyboard::GetInstance()->KeyDown(VK_2)) { _selectedType = TILE_TYPE_START; _selectedTypeColor = RGB(100, 255, 100);}
	//����
	else if (Keyboard::GetInstance()->KeyDown(VK_3)) { _selectedType = TILE_TYPE_END; _selectedTypeColor = RGB(255, 100, 100);}
	//���ϋ�
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
					//�������� �� ������ ����
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
			if (_tile[i][j].type == TILE_TYPE_EMPTY)                     //�Ϲ�Ÿ��
			{
				_tile[i][j].walkable = true;
				_tile[i][j].liston = false;
			}
			else if (_tile[i][j].type == TILE_TYPE_WALL)                 //����Ÿ��
			{
				_tile[i][j].walkable = false;
				_tile[i][j].liston = false;
			}
			else if (_tile[i][j].type == TILE_TYPE_START)                //��������
			{
				_tile[i][j].walkable = true;
				_tile[i][j].liston = true;
				_closeList.push_back(&_tile[i][j]);
			}
			else if (_tile[i][j].type == TILE_TYPE_END)                  //��������
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
	Ci = _closeList[_lastIndex]->i;                  //���������� �߰��� Ŭ���� ����Ʈ�� i
	Cj = _closeList[_lastIndex]->j;                  //���������� �߰��� Ŭ���� ����Ʈ�� j
	Cg = _closeList[_lastIndex]->G;                  //���������� �߰��� Ŭ���� ����Ʈ�� G

	if (Ci != 0)      //0��° ���� �ƴ϶�� ��� ���� ���
	{
		if (_tile[Ci - 1][Cj].walkable)     //��� ��� Ÿ���� ������ �� �ִٸ�
		{
			if (!_tile[Ci - 1][Cj].liston)  //���¸���Ʈ�� ������ �� �Ǿ� �ִ� Ÿ���̶��
			{
				_tile[Ci - 1][Cj].liston = true;  //���¸���Ʈ�� ���ԵǾ���
				_tile[_endY][_endX].vertices[0].color = 0xFF0FFFF0;
				_tile[_endY][_endX].vertices[1].color = 0xFF0FFFF0;
				_tile[_endY][_endX].vertices[2].color = 0xFF0FFFF0;
				_tile[_endY][_endX].vertices[3].color = 0xFF0FFFF0;
				_tile[Ci - 1][Cj].G = Cg + 10;//Ÿ���� G���� Ŭ���� ����Ʈ�� ���� G + 10
				_tile[Ci - 1][Cj].parent = _closeList[_lastIndex];  //Ÿ���� �θ� Ŭ���� ����Ʈ�� ���������� �߰��� Ÿ�Ϸ� ����
				_openList.push_back(&_tile[Ci - 1][Cj]);  //���¸���Ʈ ���Ϳ� �߰�
			}//liton false
			else     //���¸���Ʈ�� ������ �Ǿ� �ִ� Ÿ���̶��
			{
				if (Cg + 10 < _tile[Ci - 1][Cj].G)//���� G������ ���� ����� G���� �۴ٸ�
				{
					_tile[Ci - 1][Cj].G = Cg + 10;  //G�� ���Ӱ� ���
					_tile[Ci - 1][Cj].parent = _closeList[_lastIndex]; //Ÿ���� �θ�  Ŭ���� ����Ʈ�� ���������� �߰��� Ÿ�Ϸ� �缳��
				}
			}//liston true
		}//wakeable
		if (Cj != 0)      //�»�� : 0��° ���� �ƴ϶��
		{
			if (_tile[Ci - 1][Cj - 1].walkable && _tile[Ci - 1][Cj].walkable && _tile[Ci][Cj - 1].walkable)  //�»�� Ÿ���� �����̳� �Ʒ��� ���� ���ٸ�
			{
				if (!_tile[Ci - 1][Cj - 1].liston)
				{
					_tile[Ci - 1][Cj - 1].liston = true;
					_tile[_endY][_endX].vertices[0].color = 0xFF0FFFF0;
					_tile[_endY][_endX].vertices[1].color = 0xFF0FFFF0;
					_tile[_endY][_endX].vertices[2].color = 0xFF0FFFF0;
					_tile[_endY][_endX].vertices[3].color = 0xFF0FFFF0;
					_tile[Ci - 1][Cj - 1].G = Cg + 14;	//�밢���̹Ƿ� G + 14
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
		if (Cj != TILE_X - 1)   //���� : ������ ���� �ƴ϶��
		{
			if (_tile[Ci - 1][Cj + 1].walkable && _tile[Ci - 1][Cj].walkable && _tile[Ci][Cj + 1].walkable)  //���� Ÿ���� �����̳� �Ʒ��� ���� ���ٸ�
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

	if (Cj != 0)      //���� : 0��° ���� �ƴ϶��
	{
		if (_tile[Ci][Cj - 1].walkable) //���� Ÿ���� �̵������ϴٸ�
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

	if (Cj != TILE_X - 1) //���� : ������ ���� �ƴ϶��
	{
		if (_tile[Ci][Cj + 1].walkable) //���� Ÿ���� �̵������ϴٸ�
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

	if (Ci != TILE_Y - 1)   //������ ���� �ƴ϶�� �ϴ� ���� ���
	{
		if (_tile[Ci + 1][Cj].walkable) //�ϴ� ��� Ÿ���� �̵������ϴٸ�
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
		if (Cj != 0)            //���ϴ� : 0��° ���� �ƴ϶��
		{
			if (_tile[Ci + 1][Cj - 1].walkable && _tile[Ci + 1][Cj].walkable &&_tile[Ci][Cj - 1].walkable)   //���ϴ� Ÿ���� �������̳� ���� ���� ���ٸ�
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
		if (Cj != TILE_X - 1)          //���ϴ� : ������ ���� �ƴ϶��
		{
			if (_tile[Ci + 1][Cj + 1].walkable && _tile[Ci + 1][Cj].walkable &&_tile[Ci][Cj + 1].walkable) //���ϴ� Ÿ���� �������̳� ���� �̵������ϴٸ�
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
		int vertical = (_endX - _openList[i]->j) * 10;     //���� H��
		int horizontal = (_endY - _openList[i]->i) * 10;   //���� H��

		if (vertical < 0) vertical *= -1;			//������ �ݴ��̸� ���� �ο�(���밪)
		if (horizontal < 0) horizontal *= -1;

		_openList[i]->H = vertical + horizontal;    //�� H�� = ����H + ����H
	}

}

void aStar::CalculateF()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		_openList[i]->F = _openList[i]->G + _openList[i]->H;               //F�� ���
	}
}


void aStar::AddCloseList()
{
	if (_openList.size() == 0)//�˻��ߴµ��� openlist�� ����� 0�̶�� ���̻� ã�� ���� ����
	{
		_aStarState = ASTAR_STATE_NOWAY; //��ΰ� ����
		return;                          //���� �۾� ����
	}

	int index = 0;                 //���¸���Ʈ �� ���� F�� ���� Ÿ���� �ε���
	int lowest = BIGNUM;           //���¸���Ʈ �� ���� ���� F��
	for (int i = 0; i < _openList.size(); i++)
	{
		if (_openList[i]->F < lowest) //���¸���Ʈ�� F�� ���� �����ź��� �� �۴ٸ�
		{
			lowest = _openList[i]->F;   //lowest�� �� F��
			index = i;                  //index�� �� index��
		}
	}

	_openList[index]->vertices[0].color = RGB(180, 180, 255); //Ŭ��� �߰��� Ÿ���� ���� : ���Ķ�
	_openList[index]->vertices[1].color = RGB(180, 180, 255); //Ŭ��� �߰��� Ÿ���� ���� : ���Ķ�
	_openList[index]->vertices[2].color = RGB(180, 180, 255); //Ŭ��� �߰��� Ÿ���� ���� : ���Ķ�
	_openList[index]->vertices[3].color = RGB(180, 180, 255);

	_closeList.push_back(_openList[index]);       //Ŭ�����Ʈ�� �߰�
	_openList.erase(_openList.begin() + index);   //Ŭ�����Ʈ�� �߰��� Ÿ���� ���¸���Ʈ���� ����

	_lastIndex++;                                   //���� ���߿� �߰��� Ŭ������ �ε���
}

void aStar::CheckArrive()
{
	if (_closeList[_lastIndex]->i == _endY && _closeList[_lastIndex]->j == _endX) //Ŭ�����Ʈ�� i j�� ���������� ���ٸ�
	{
		_aStarState = ASTAR_STATE_FOUND;                      //ã�Ҵ�
		
		_closeList[_lastIndex]->vertices[0].color = 0xFF0000000;//�������� ���� ����
		_closeList[_lastIndex]->vertices[1].color = 0xFF0000000;//�������� ���� ����
		_closeList[_lastIndex]->vertices[2].color = 0xFF0000000;//�������� ���� ����
		_closeList[_lastIndex]->vertices[3].color = 0xFF0000000;//�������� ���� ����
		ShowWay(_closeList[_lastIndex]);                    //��� �����ش�
	}
}

void aStar::ShowWay(aStarTile * tile)
{
	if (!(tile->i == _endY && tile->j == _endX))	//���������� �ƴ϶��
	{
		tile->vertices[0].color = RGB(255, 180, 180);				//���� ����ȫ
		tile->vertices[1].color = RGB(255, 180, 180);				//���� ����ȫ
		tile->vertices[2].color = RGB(255, 180, 180);				//���� ����ȫ
		tile->vertices[3].color = RGB(255, 180, 180);				//���� ����ȫ

	}
	tile = tile->parent;								//Ÿ���� �θ� �����ؼ� showWay()�Լ��� �ٽ� �ִ´�

	if (tile->parent == NULL)							//Ÿ���� �θ� ���������̸� �׸� ������
		return;
	else
		ShowWay(tile);								//showWay() �ٽ� ȣ��
}


