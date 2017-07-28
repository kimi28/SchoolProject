#include "stdafx.h"
#include "tank.h"
#include "TankMap.h"
#include "Rect.h"
#include "Animation.h"
#include "Intersect.h"
tank::tank(LPDIRECT3DDEVICE9 device)
	:device(device)
{
	init();
}

tank::~tank()
{
}

HRESULT tank::init()
{
	//탱크 방향 초기화
	_direction = TANKDIRECTION_RIGHT;
	_x = 0;
	_y = 0;
	//탱크 프레임 이미지 초기화
	_animation = new Animation(device, L"Textures/tank.bmp", { 8,4 }, { _x,_y });
	
	//탱크 속도
	_speed = 1.0f;
	frame = { 0,0 };
	
	

	return S_OK;
}

void tank::release()
{
	SAFE_DELETE(_animation);
}

void tank::update()
{
	//왼쪽 
	if (Keyboard::GetInstance()->KeyPress(VK_LEFT))
	{
		_direction = TANKDIRECTION_LEFT;
		tankMove();
	}

	if (Keyboard::GetInstance()->KeyPress(VK_RIGHT))
	{
		_direction = TANKDIRECTION_RIGHT;
		tankMove();
	}

	if (Keyboard::GetInstance()->KeyPress(VK_UP))
	{
		_direction = TANKDIRECTION_UP;
		tankMove();
	}

	if (Keyboard::GetInstance()->KeyPress(VK_DOWN))
	{
		_direction = TANKDIRECTION_DOWN;
		tankMove();
	}
	_rc = { (LONG)_x, (LONG)_y, (LONG)_x+TILESIZE, (LONG)_y + TILESIZE };
	_animation->Update(frame);

	WCHAR str[255];
	wsprintf(str, L"[0] : %d, [1] : %d ", tileIndex[0], tileIndex[1]);
	PrintText::GetInstance()->AddText(str);
}

void tank::render()
{
	_animation->Render();
	PrintText::GetInstance()->Render();
	
}

void tank::tankMove()
{

	RECT rcCollision;	//충돌 렉트
	int tileX, tileY;	//타일 x,y
	rcCollision = _rc;

	float elapsedTime = Timer::GetInstance()->getElapsedTime();
	float moveSpeed = elapsedTime * _speed;
	switch (_direction)
	{
	case TANKDIRECTION_LEFT:
		frame = { 0,3 };
		_x -= 1.0f;
		_animation->SetCoord({ _x, _y });

		rcCollision = { (LONG)_x, (LONG)_y, (LONG)_x + TILESIZE, (LONG)_y + TILESIZE };

		break;

	case TANKDIRECTION_RIGHT:
		frame = { 0,2 };
		_x += 1.0f;
		_animation->SetCoord({ _x, _y });

		rcCollision = { (LONG)_x, (LONG)_y,(LONG)_x + TILESIZE, (LONG)_y + TILESIZE };

		break;

	case TANKDIRECTION_UP:
		frame = { 0,0 };
		_y -= 1.0f;
		_animation->SetCoord({ _x, _y });

		rcCollision = { (LONG)_x, (LONG)_y,(LONG)_x + TILESIZE, (LONG)_y + TILESIZE };

		break;

	case TANKDIRECTION_DOWN:
		frame = { 0,1 };
		_y += 1.0f;
		_animation->SetCoord({ _x, _y });

		rcCollision = { (LONG)_x, (LONG)_y, (LONG)_x+TILESIZE, (LONG)_y + TILESIZE };

		break;
	}
	rcCollision.left += 1;
	rcCollision.top += 1;
	rcCollision.right -= 1;
	rcCollision.bottom -= 1;

	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;

	switch (_direction)
	{

	case TANKDIRECTION_LEFT:
		tileIndex[0] = tileX + tileY * TILEX;		//탱크가 밟고있는 인덱스
		tileIndex[1] = tileIndex[0]-1;	//탱크 밟고있는 인덱스 왼쪽
		break;
	case TANKDIRECTION_RIGHT:
		tileIndex[0] = (tileX + tileY * TILEX);	//탱크가 밟고있는 인덱스
		tileIndex[1] = tileIndex[0] + 1;	//탱크 밟고있는 인덱스 오른쪽
		break;
	case TANKDIRECTION_UP:
		tileIndex[0] = tileX + tileY * TILEY;
		tileIndex[1] = tileIndex[0] -20;
		break;
	case TANKDIRECTION_DOWN:
		tileIndex[0] = (tileX + tileY * TILEY);
		tileIndex[1] = tileIndex[0] +20;
		break;
	}
	if (tileIndex[1] < 0 || tileIndex[1] >400)
	{
		tileIndex[1] = tileIndex[0];
	}

	for (int i = 0; i < 2; i++)
	{
		RECT rc;
		if (((_tankMap->getAttribute()[tileIndex[i]] & ATTR_UNMOVE) == ATTR_UNMOVE) &&
			IntersectRect(&rc, &_tankMap->getTiles()[tileIndex[i]].rc->GetRect(), &rcCollision))
		{
			switch (_direction)
			{
				//움직이려 할때 갈수 없는 지역이면 탱크의 움직임을 고정시킴
				//ex : 탱크가 왼쪽으로 갈때 왼쪽지역이 갈수 없으면
			case TANKDIRECTION_LEFT:
				_rc.left = _tankMap->getTiles()[tileIndex[i]].rc->GetRect().right;	//왼쪽 타일의 라이트의 위치를 탱크의 래프트의 위치로 고정
				_rc.right = _rc.left+30;								//탱크크기만큼
				_x = _rc.left;				//탱크 x의 위치를 계산한 탱크 렉트의 위치값으로 설정(중앙으로)
				break;
			case TANKDIRECTION_RIGHT:
				_rc.right = _tankMap->getTiles()[tileIndex[i]].rc->GetRect().left;	//왼쪽 타일의 라이트의 위치를 탱크의 래프트의 위치로 고정
				_rc.left = _rc.right-30;								//탱크크기만큼
				_x = _rc.left;				//탱크 x의 위치를 계산한 탱크 렉트의 위치값으로 설정(중앙으로
				break;
			case TANKDIRECTION_UP:
				_rc.top = _tankMap->getTiles()[tileIndex[i]].rc->GetRect().bottom;	//왼쪽 타일의 라이트의 위치를 탱크의 래프트의 위치로 고정
				_rc.bottom = _rc.top+30;								//탱크크기만큼
				_y = _rc.top ;				//탱크 x의 위치를 계산한 탱크 렉트의 위치값으로 설정(중앙으로)

				break;
			case TANKDIRECTION_DOWN:
				_rc.bottom = _tankMap->getTiles()[tileIndex[i]].rc->GetRect().top;	//왼쪽 타일의 라이트의 위치를 탱크의 래프트의 위치로 고정
				_rc.top = _rc.bottom-30 ;								//탱크크기만큼
				_y = _rc.top;			//탱크 x의 위치를 계산한 탱크 렉트의 위치값으로 설정(중앙으로)
				break;
			}
			_animation->SetCoord({ _x, _y });
			rcCollision = { (LONG)_x, (LONG)_y, (LONG)_x + TILESIZE, (LONG)_y + TILESIZE };

		}
	}

	//_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}
