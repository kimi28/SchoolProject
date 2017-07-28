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

		//클릭한 좌표가 시작x로부터 얼마나 멀리 떨어져서 클릭이
		//되었는가 몫으로 검출 만일 400보다 왼쪽이라면 바로 -1을
		//적용시켜줘야함. 그래야 하나의 iso 타일에 렉트를 적용시ㅕㅋ
		//검출 할수 있기 때문

		if (cellX < 0)
		{
			cellX = (cellX - CELL_WIDTH) / CELL_WIDTH;
 		}

		else
		{
			//얼만큼 떨어져서 클릭했는가(가로지름기준)을 수치화
			cellX = cellX / (float)CELL_WIDTH;
		}

		//y는 - 개념이 없기떄문에(기준점이 가장 위) 절대값으로 구함
		int cellY = abs(Mouse::GetInstance()->GetPosition().y - INIT_Y) / CELL_HEIGHT;

		//만약 시작점 자체가 - 일 수 있기때문에 -라면 -1을 곱해준다
		cellY = (Mouse::GetInstance()->GetPosition().y < INIT_Y) ? cellY * -1 : cellY;

		//x는 y가 기준점에 가까워질수록 작아져야 한다.
		//마름모기 떄문에 X축은 Y기준값으로부터 멀리 떨어질수록 X 값은 커진다.
		int isoX = (int)cellX + (int)cellY;
		//y는 x가 -로 갈수록 커져야 한다.
		//Y축은 X기준값으로부터 멀리 떨어질수록 Y는 늘어나게 된다.
		int isoY = (int)cellY - (int)cellX;

		//만약 x좌표가 0보다 크고 최대타일수 보다 작고
		//Y좌표 0보다 크고, 최대타일수보다 작으면 검출대상에 집어넣자
		if (isoX >= 0 && isoX < TILE_COUNT_X &&
			isoY >= 0 && isoY < TILE_COUNT_Y)
		{
			//1분면이면[x - 1][y]
			//2분면이면[x][y - 1]
			//3분면이면[x1][y + 1]
			//4분면이면[x + 1][y]

			//코너 검출(어느 분면에 찍혔는지)
			int corner = getCornerIndex(isoX, isoY);

			//만일 4분면이 검출되었는데, 그게 마름모안에 있는지 확인
			if (isInRhombus(corner, isoX, isoY))
			{
				//만약 들어가 있다면 지금의 isoX, isoY는 건들 필요 없다
				//마름모 안에 들어가 있기 때문에 예외처리를 할 필요가 없다
				//만약 이 값이 false가 되었다면 마롬므가 아닌 그 밖에 찍혔다는 뜻이 되므로
				//다른 타일을 눌렀다는 것이 되고 거기에 따른 예외처리는 밑에서 써주면 된다.

				corner = 0;
			}

			_corner = corner;
			_isoX = isoX;
			_isoY = isoY;

			//만약 마름모 안에 클릭한게 아니라면
			switch (corner)
			{
				//만약 1/4분면에서 마름모 안에 찍힌게 아니라면 그 위의 마름모가 찍히게 된다
			case 1:
				isoX = isoX - 1;	//마름모의 4변중에 좌측 위변과 맞닿아 있는 마름모는 X축으로 한단계 낮은 죄표이다.
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
			//그래서 해당 좌표의 데이터를 0에서 1로 바꿔주어 클릭했다고 값을 바꿔주면 됨
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
	//클릭한 좌표점을 통해서 해당공식을 통해 렉트의 left, top을 구한다
	int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
	int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

	int right = left + CELL_WIDTH;
	int bottom = top + CELL_HEIGHT;

	//마우스 좌표 마름모안에 있을떄 비율을 기준으로 4분면을 구함
	//left top : 1,  right top :2 , left bottom : 3 ,right bottom : 4

	//left에서 마우스값을 빼면 레프트에서 이동한 값만 남는데,
	//이걸 전체길이로 나누면 0.0~ 1.0 (float으로 나눴고 , 변수가 float이니까)의 값이 나온다
	//비율값으로 마름모를 포함한 렉트를 1~4분으로 나웠을때
	//찍은 위치를 알 수 있다.

	float dx = (Mouse::GetInstance()->GetPosition().x - left) / (float)CELL_WIDTH;
	float dy = (Mouse::GetInstance()->GetPosition().y - top) / (float)CELL_HEIGHT;

	//만약 둘다 중점(0.5)보다 작으면 1/4분면
	if (dx < 0.5f && dy < 0.5f) return 1;
	//만약 dx 중점(0.5)보다 크면 2/4분면
	if (dx >= 0.5f && dy < 0.5f) return 2;
	//만약 dx 중점(0.5)보다 작고 dy 중점보다 크면 3/4분면
	if (dx < 0.5f && dy >= 0.5f) return 3;
	//만약 둘다 중점(0.5)보다 크면 4/4
	if (dx >= 0.5f && dy >= 0.5f) return 4;

	return 0;
}

bool isoTest::isInRhombus(int corner, int isoX, int isoY)
{
	//1/4분면 안에 있으면
	if (corner == 1)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		//left 에서 마우스값을 뺀값(left에서 이동거리)를
		//left와 중점폭으로 top과 중점을 길이로 하는 작은 사각형으로 
		//비례하기 위해 dx와 dy를 구한다.
		float dx = (float)(Mouse::GetInstance()->GetPosition().x - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(Mouse::GetInstance()->GetPosition().y - top) / (CELL_HEIGHT / 2.0f);

		//만약 전체 비례즁에서 정삼각형 안에 들어가야 하기 때문에
		//무조건 dy가 dx보다 같거나 작을 수 밖에 없다.
		//정삼각형 안에 들어가 잇는 점은 무조건 y가 x보다 작거나 
		//같을 수 밖에 없다.

		//1뺴주는 이유는 top에서부터 차이를 계산 했기 떄무에
		//바텀에서부터의 값을 구하기 위함

		if ((1.0f - dy) <= dx) return true;

		//정삼각형 밖에 있다면 
		else return false;
	}

	//2/4분면 안에 있으면
	else if (corner == 2)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		//레프트의 중점의 절반을 더하는 이유는
		//검사하는 렉트가 실질적으로 마름모의 시작점인 left가
		//아닌 중점에서의 작은 렉트(사각형)이기 때문에
		//가로 반지름을 더한다
		left += (CELL_WIDTH / 2.0f);
		
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		//left 에서 마우스값을 뺀값(left에서 이동거리)를
		//left와 중점폭으로 top과 중점을 길이로 하는 작은 사각형으로 
		//비례하기 위해 dx와 dy를 구한다.
		float dx = (float)(Mouse::GetInstance()->GetPosition().x - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(Mouse::GetInstance()->GetPosition().y - top) / (CELL_HEIGHT / 2.0f);

		//만약 전체 비례즁에서 정삼각형 안에 들어가야 하기 때문에
		//무조건 dy가 dx보다 같거나 작을 수 밖에 없다.
		//정삼각형 안에 들어가 잇는 점은 무조건 y가 x보다 작거나 
		//같을 수 밖에 없다.

		//1뺴주는 이유는 top에서부터 차이를 계산 했기 떄무에
		//바텀에서부터의 값을 구하기 위함

		if (dy >= dx) return true;

		//정삼각형 밖에 있다면 
		else return false;
	}

	//3/4분면 안에 있으면
	else if (corner == 3)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);
		
		top += (CELL_HEIGHT / 2.0f);

		//left 에서 마우스값을 뺀값(left에서 이동거리)를
		//left와 중점폭으로 top과 중점을 길이로 하는 작은 사각형으로 
		//비례하기 위해 dx와 dy를 구한다.
		float dx = (float)(Mouse::GetInstance()->GetPosition().x - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(Mouse::GetInstance()->GetPosition().y - top) / (CELL_HEIGHT / 2.0f);

		//만약 전체 비례즁에서 정삼각형 안에 들어가야 하기 때문에
		//무조건 dy가 dx보다 같거나 작을 수 밖에 없다.
		//정삼각형 안에 들어가 잇는 점은 무조건 y가 x보다 작거나 
		//같을 수 밖에 없다.

		//1뺴주는 이유는 top에서부터 차이를 계산 했기 떄무에
		//바텀에서부터의 값을 구하기 위함

		if (dy <= dx) return true;

		//정삼각형 밖에 있다면 
		else return false;
	}

	//4/4분면 안에 있으면
	else if (corner == 4)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		left += (CELL_WIDTH / 2.0f);
		top += (CELL_HEIGHT / 2.0f);

		//left 에서 마우스값을 뺀값(left에서 이동거리)를
		//left와 중점폭으로 top과 중점을 길이로 하는 작은 사각형으로 
		//비례하기 위해 dx와 dy를 구한다.
		float dx = (float)(Mouse::GetInstance()->GetPosition().x - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(Mouse::GetInstance()->GetPosition().y - top) / (CELL_HEIGHT / 2.0f);

		//만약 전체 비례즁에서 정삼각형 안에 들어가야 하기 때문에
		//무조건 dy가 dx보다 같거나 작을 수 밖에 없다.
		//정삼각형 안에 들어가 잇는 점은 무조건 y가 x보다 작거나 
		//같을 수 밖에 없다.

		//1뺴주는 이유는 top에서부터 차이를 계산 했기 떄무에
		//바텀에서부터의 값을 구하기 위함

		if ((1.0f - dy) >= dx) return true;

		//정삼각형 밖에 있다면 
		else return false;
	}

}
