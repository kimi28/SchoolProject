#include "stdafx.h"
#include "isoTest.h"
#include "Scene.h"
isoTest::isoTest(LPDIRECT3DDEVICE9 device)
	:device(device)
{
	
}

isoTest::~isoTest()
{
}

void isoTest::Initialize()
{
	_tileMap[TILE_COUNT_X][TILE_COUNT_Y] = 0;
	_isoX = 0;
	_isoY = 0;
	_corner = 0;
	memset(_tileMap, 0, sizeof(_tileMap));

	HRESULT hr;
	hr = D3DXCreateLine(device, &line);
	assert(SUCCEEDED(hr));
}

void isoTest::Destroy()
{
	line->Release();
}

void isoTest::Update()
{
	if (Mouse::GetInstance()->ButtonPress(0))
	{
		float cellX = (float)(Mouse::GetInstance()->GetPosition().x - INIT_X);

		//Ŭ���� ��ǥ�� ����x�κ��� �󸶳� �ָ� �������� Ŭ����
		//�Ǿ��°� ������ ���� ���� 400���� �����̶�� �ٷ� -1��
		//������������. �׷��� �ϳ��� iso Ÿ�Ͽ� ��Ʈ�� ����äŤ�
		//���� �Ҽ� �ֱ� ����

		if (cellX < 0)
		{
			cellX = (cellX - CELL_WIDTH) / CELL_WIDTH;
 		}

		else
		{
			//��ŭ �������� Ŭ���ߴ°�(������������)�� ��ġȭ
			cellX = cellX / (float)CELL_WIDTH;
		}

		//y�� - ������ ���⋚����(�������� ���� ��) ���밪���� ����
		int cellY = abs(Mouse::GetInstance()->GetPosition().y - INIT_Y) / CELL_HEIGHT;

		//���� ������ ��ü�� - �� �� �ֱ⶧���� -��� -1�� �����ش�
		cellY = (Mouse::GetInstance()->GetPosition().y < INIT_Y) ? cellY * -1 : cellY;

		//x�� y�� �������� ����������� �۾����� �Ѵ�.
		//������� ������ X���� Y���ذ����κ��� �ָ� ���������� X ���� Ŀ����.
		int isoX = (int)cellX + (int)cellY;
		//y�� x�� -�� ������ Ŀ���� �Ѵ�.
		//Y���� X���ذ����κ��� �ָ� ���������� Y�� �þ�� �ȴ�.
		int isoY = (int)cellY - (int)cellX;

		//���� x��ǥ�� 0���� ũ�� �ִ�Ÿ�ϼ� ���� �۰�
		//Y��ǥ 0���� ũ��, �ִ�Ÿ�ϼ����� ������ ������ �������
		if (isoX >= 0 && isoX < TILE_COUNT_X &&
			isoY >= 0 && isoY < TILE_COUNT_Y)
		{
			//1�и��̸�[x - 1][y]
			//2�и��̸�[x][y - 1]
			//3�и��̸�[x1][y + 1]
			//4�и��̸�[x + 1][y]

			//�ڳ� ����(��� �и鿡 ��������)
			int corner = getCornerIndex(isoX, isoY);

			//���� 4�и��� ����Ǿ��µ�, �װ� ������ȿ� �ִ��� Ȯ��
			if (isInRhombus(corner, isoX, isoY))
			{
				//���� �� �ִٸ� ������ isoX, isoY�� �ǵ� �ʿ� ����
				//������ �ȿ� �� �ֱ� ������ ����ó���� �� �ʿ䰡 ����
				//���� �� ���� false�� �Ǿ��ٸ� ���ҹǰ� �ƴ� �� �ۿ� �����ٴ� ���� �ǹǷ�
				//�ٸ� Ÿ���� �����ٴ� ���� �ǰ� �ű⿡ ���� ����ó���� �ؿ��� ���ָ� �ȴ�.

				corner = 0;
			}

			_corner = corner;
			_isoX = isoX;
			_isoY = isoY;

			//���� ������ �ȿ� Ŭ���Ѱ� �ƴ϶��
			switch (corner)
			{
				//���� 1/4�и鿡�� ������ �ȿ� ������ �ƴ϶�� �� ���� ������ ������ �ȴ�
			case 1:
				isoX = isoX - 1;	//�������� 4���߿� ���� ������ �´�� �ִ� ������� X������ �Ѵܰ� ���� ��ǥ�̴�.
				break;
			case 2:
				isoY = isoY - 1;
				break;
			case 3:
				isoY = isoY + 1;
				break;
			case 4:
				isoX = isoX + 1;
				break;
			}
			//�׷��� �ش� ��ǥ�� �����͸� 0���� 1�� �ٲ��־� Ŭ���ߴٰ� ���� �ٲ��ָ� ��
			_tileMap[isoX][isoY] = 1;


		}
	}
	

}

void isoTest::Render()
{
	//wsprintf(str, L"isoX : %d, isoY : %d, corner : %d", _isoX, _isoY, _corner);
	
	drawTileMap();

	wsprintf(str, L"isoX : %d, isoY : %d, corner : %d", _isoX, _isoY, _corner);

	PrintText::GetInstance()->SetCoord({ 900,20 });
	PrintText::GetInstance()->AddText(str);
	PrintText::GetInstance()->Render();
}

void isoTest::drawTileMap()
{
	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);


	D3DXMATRIX ortho;
	D3DXMatrixOrthoOffCenterLH(&ortho, 0, viewport.Width, viewport.Height, 0, 0, 1);

	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			int left = INIT_X + (i * RADIUS_WIDTH) - (j * RADIUS_WIDTH);
			int top = INIT_Y + (i * RADIUS_HEIGHT) + (j * RADIUS_HEIGHT);

			int centerX = left + RADIUS_WIDTH;
			int centerY = top + RADIUS_HEIGHT;

			
			if (_tileMap[i][j] == 1)
			{
				lineColor = 0xFFFF0000;
				line->SetWidth(2);
			}
			else
			{
				lineColor = 0xFF000000;
				line->SetWidth(1);

			}
		
			drawRhombus(left, top);

			line->Begin();
			line->DrawTransform(lineVector, 5, &ortho, lineColor);
			line->End();

			wsprintf(str, L"(%d, %d)", i, j);
			
			PrintText::GetInstance()->SetCoord({ centerX,centerY });
			PrintText::GetInstance()->AddText(str);
			PrintText::GetInstance()->Render();
		}
	}
}

void isoTest::drawRhombus(int left, int top)
{
	int centerX = left + RADIUS_WIDTH;
	int centerY = top + RADIUS_HEIGHT;

	lineVector[0].x = centerX;
	lineVector[0].y = centerY - RADIUS_HEIGHT;
	lineVector[0].z = 0;

	lineVector[1].x = centerX + RADIUS_WIDTH;
	lineVector[1].y = centerY;
	lineVector[1].z = 0;

	lineVector[2].x = centerX;
	lineVector[2].y = centerY + RADIUS_HEIGHT;
	lineVector[2].z = 0;

	lineVector[3].x = centerX - RADIUS_WIDTH;
	lineVector[3].y = centerY;
	lineVector[3].z = 0;

	lineVector[4].x = centerX;
	lineVector[4].y = centerY - RADIUS_HEIGHT;
	lineVector[4].z = 0;
}

int isoTest::getCornerIndex(int isoX, int isoY)
{
	//Ŭ���� ��ǥ���� ���ؼ� �ش������ ���� ��Ʈ�� left, top�� ���Ѵ�
	int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
	int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

	int right = left + CELL_WIDTH;
	int bottom = top + CELL_HEIGHT;

	//���콺 ��ǥ ������ȿ� ������ ������ �������� 4�и��� ����
	//left top : 1,  right top :2 , left bottom : 3 ,right bottom : 4

	//left���� ���콺���� ���� ����Ʈ���� �̵��� ���� ���µ�,
	//�̰� ��ü���̷� ������ 0.0~ 1.0 (float���� ������ , ������ float�̴ϱ�)�� ���� ���´�
	//���������� ������ ������ ��Ʈ�� 1~4������ ��������
	//���� ��ġ�� �� �� �ִ�.

	float dx = (Mouse::GetInstance()->GetPosition().x - left) / (float)CELL_WIDTH;
	float dy = (Mouse::GetInstance()->GetPosition().y - top) / (float)CELL_HEIGHT;

	//���� �Ѵ� ����(0.5)���� ������ 1/4�и�
	if (dx < 0.5f && dy < 0.5f) return 1;
	//���� dx ����(0.5)���� ũ�� 2/4�и�
	if (dx >= 0.5f && dy < 0.5f) return 2;
	//���� dx ����(0.5)���� �۰� dy �������� ũ�� 3/4�и�
	if (dx < 0.5f && dy >= 0.5f) return 3;
	//���� �Ѵ� ����(0.5)���� ũ�� 4/4
	if (dx >= 0.5f && dy >= 0.5f) return 4;

	return 0;
}

bool isoTest::isInRhombus(int corner, int isoX, int isoY)
{
	//1/4�и� �ȿ� ������
	if (corner == 1)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		//left ���� ���콺���� ����(left���� �̵��Ÿ�)��
		//left�� ���������� top�� ������ ���̷� �ϴ� ���� �簢������ 
		//����ϱ� ���� dx�� dy�� ���Ѵ�.
		float dx = (float)(Mouse::GetInstance()->GetPosition().x - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(Mouse::GetInstance()->GetPosition().y - top) / (CELL_HEIGHT / 2.0f);

		//���� ��ü ��ʣO���� ���ﰢ�� �ȿ� ���� �ϱ� ������
		//������ dy�� dx���� ���ų� ���� �� �ۿ� ����.
		//���ﰢ�� �ȿ� �� �մ� ���� ������ y�� x���� �۰ų� 
		//���� �� �ۿ� ����.

		//1���ִ� ������ top�������� ���̸� ��� �߱� ������
		//���ҿ��������� ���� ���ϱ� ����

		if ((1.0f - dy) <= dx) return true;

		//���ﰢ�� �ۿ� �ִٸ� 
		else return false;
	}

	//2/4�и� �ȿ� ������
	else if (corner == 2)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		//����Ʈ�� ������ ������ ���ϴ� ������
		//�˻��ϴ� ��Ʈ�� ���������� �������� �������� left��
		//�ƴ� ���������� ���� ��Ʈ(�簢��)�̱� ������
		//���� �������� ���Ѵ�
		left += (CELL_WIDTH / 2.0f);
		
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		//left ���� ���콺���� ����(left���� �̵��Ÿ�)��
		//left�� ���������� top�� ������ ���̷� �ϴ� ���� �簢������ 
		//����ϱ� ���� dx�� dy�� ���Ѵ�.
		float dx = (float)(Mouse::GetInstance()->GetPosition().x - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(Mouse::GetInstance()->GetPosition().y - top) / (CELL_HEIGHT / 2.0f);

		//���� ��ü ��ʣO���� ���ﰢ�� �ȿ� ���� �ϱ� ������
		//������ dy�� dx���� ���ų� ���� �� �ۿ� ����.
		//���ﰢ�� �ȿ� �� �մ� ���� ������ y�� x���� �۰ų� 
		//���� �� �ۿ� ����.

		//1���ִ� ������ top�������� ���̸� ��� �߱� ������
		//���ҿ��������� ���� ���ϱ� ����

		if (dy >= dx) return true;

		//���ﰢ�� �ۿ� �ִٸ� 
		else return false;
	}

	//3/4�и� �ȿ� ������
	else if (corner == 3)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);
		
		top += (CELL_HEIGHT / 2.0f);

		//left ���� ���콺���� ����(left���� �̵��Ÿ�)��
		//left�� ���������� top�� ������ ���̷� �ϴ� ���� �簢������ 
		//����ϱ� ���� dx�� dy�� ���Ѵ�.
		float dx = (float)(Mouse::GetInstance()->GetPosition().x - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(Mouse::GetInstance()->GetPosition().y - top) / (CELL_HEIGHT / 2.0f);

		//���� ��ü ��ʣO���� ���ﰢ�� �ȿ� ���� �ϱ� ������
		//������ dy�� dx���� ���ų� ���� �� �ۿ� ����.
		//���ﰢ�� �ȿ� �� �մ� ���� ������ y�� x���� �۰ų� 
		//���� �� �ۿ� ����.

		//1���ִ� ������ top�������� ���̸� ��� �߱� ������
		//���ҿ��������� ���� ���ϱ� ����

		if (dy <= dx) return true;

		//���ﰢ�� �ۿ� �ִٸ� 
		else return false;
	}

	//4/4�и� �ȿ� ������
	else if (corner == 4)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		left += (CELL_WIDTH / 2.0f);
		top += (CELL_HEIGHT / 2.0f);

		//left ���� ���콺���� ����(left���� �̵��Ÿ�)��
		//left�� ���������� top�� ������ ���̷� �ϴ� ���� �簢������ 
		//����ϱ� ���� dx�� dy�� ���Ѵ�.
		float dx = (float)(Mouse::GetInstance()->GetPosition().x - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(Mouse::GetInstance()->GetPosition().y - top) / (CELL_HEIGHT / 2.0f);

		//���� ��ü ��ʣO���� ���ﰢ�� �ȿ� ���� �ϱ� ������
		//������ dy�� dx���� ���ų� ���� �� �ۿ� ����.
		//���ﰢ�� �ȿ� �� �մ� ���� ������ y�� x���� �۰ų� 
		//���� �� �ۿ� ����.

		//1���ִ� ������ top�������� ���̸� ��� �߱� ������
		//���ҿ��������� ���� ���ϱ� ����

		if ((1.0f - dy) >= dx) return true;

		//���ﰢ�� �ۿ� �ִٸ� 
		else return false;
	}

}
