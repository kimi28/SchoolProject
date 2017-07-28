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
	//��ũ ���� �ʱ�ȭ
	_direction = TANKDIRECTION_RIGHT;
	_x = 0;
	_y = 0;
	//��ũ ������ �̹��� �ʱ�ȭ
	_animation = new Animation(device, L"Textures/tank.bmp", { 8,4 }, { _x,_y });
	
	//��ũ �ӵ�
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
	//���� 
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

	RECT rcCollision;	//�浹 ��Ʈ
	int tileX, tileY;	//Ÿ�� x,y
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
		tileIndex[0] = tileX + tileY * TILEX;		//��ũ�� ����ִ� �ε���
		tileIndex[1] = tileIndex[0]-1;	//��ũ ����ִ� �ε��� ����
		break;
	case TANKDIRECTION_RIGHT:
		tileIndex[0] = (tileX + tileY * TILEX);	//��ũ�� ����ִ� �ε���
		tileIndex[1] = tileIndex[0] + 1;	//��ũ ����ִ� �ε��� ������
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
				//�����̷� �Ҷ� ���� ���� �����̸� ��ũ�� �������� ������Ŵ
				//ex : ��ũ�� �������� ���� ���������� ���� ������
			case TANKDIRECTION_LEFT:
				_rc.left = _tankMap->getTiles()[tileIndex[i]].rc->GetRect().right;	//���� Ÿ���� ����Ʈ�� ��ġ�� ��ũ�� ����Ʈ�� ��ġ�� ����
				_rc.right = _rc.left+30;								//��ũũ�⸸ŭ
				_x = _rc.left;				//��ũ x�� ��ġ�� ����� ��ũ ��Ʈ�� ��ġ������ ����(�߾�����)
				break;
			case TANKDIRECTION_RIGHT:
				_rc.right = _tankMap->getTiles()[tileIndex[i]].rc->GetRect().left;	//���� Ÿ���� ����Ʈ�� ��ġ�� ��ũ�� ����Ʈ�� ��ġ�� ����
				_rc.left = _rc.right-30;								//��ũũ�⸸ŭ
				_x = _rc.left;				//��ũ x�� ��ġ�� ����� ��ũ ��Ʈ�� ��ġ������ ����(�߾�����
				break;
			case TANKDIRECTION_UP:
				_rc.top = _tankMap->getTiles()[tileIndex[i]].rc->GetRect().bottom;	//���� Ÿ���� ����Ʈ�� ��ġ�� ��ũ�� ����Ʈ�� ��ġ�� ����
				_rc.bottom = _rc.top+30;								//��ũũ�⸸ŭ
				_y = _rc.top ;				//��ũ x�� ��ġ�� ����� ��ũ ��Ʈ�� ��ġ������ ����(�߾�����)

				break;
			case TANKDIRECTION_DOWN:
				_rc.bottom = _tankMap->getTiles()[tileIndex[i]].rc->GetRect().top;	//���� Ÿ���� ����Ʈ�� ��ġ�� ��ũ�� ����Ʈ�� ��ġ�� ����
				_rc.top = _rc.bottom-30 ;								//��ũũ�⸸ŭ
				_y = _rc.top;			//��ũ x�� ��ġ�� ����� ��ũ ��Ʈ�� ��ġ������ ����(�߾�����)
				break;
			}
			_animation->SetCoord({ _x, _y });
			rcCollision = { (LONG)_x, (LONG)_y, (LONG)_x + TILESIZE, (LONG)_y + TILESIZE };

		}
	}

	//_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}
