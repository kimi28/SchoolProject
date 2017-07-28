#include "stdafx.h"
#include "GameMain.h"
#include "tankGameScene.h"
#include "Rect.h"
#include "Animation.h"
#include "Sprite.h"
#include "Intersect.h"
#include "isoTest.h"
#include "aStar.h"


GameMain::GameMain(HINSTANCE hInstance, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow)
	: DxWindow(hInstance, className, lpCmdLine, nCmdShow)
{
}

GameMain::~GameMain()
{
}

void GameMain::Initialize()
{
	/*m_currentTile.x = 2;
	m_currentTile.y = 0;
	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);
	_animation = new Animation(device, L"Textures/tilemap.bmp", { SAMPLETILEX,SAMPLETILEY });
	_sprite = new Sprite(device, L"Textures/tilemap.bmp", { (float)(viewport.Width - TILESIZEX) ,0 });
	_sprite->Initialize();
	maptoolSetup();

	rcTile = new Rect(device, { (float)viewport.Width - 100,(float)viewport.Height - 100 }, { 100,100 });
	rcTile->Initialize();*/

	//SceneManager::GetInstance()->AddScene("tankGameScene", new tankGameScene(device));
	//SceneManager::GetInstance()->AddScene("isoTest", new isoTest(device));
	SceneManager::GetInstance()->AddScene("aStar", new aStar(device));
	//SceneManager::GetInstance()->changeScene("tankGameScene");
	SceneManager::GetInstance()->changeScene("aStar");

	//this->vertices[0].pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//this->vertices[0].color = 0xff00ff00;

	//this->vertices[1].pos = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	//this->vertices[1].color = 0xff0000ff;

	//this->vertices[2].pos = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	//this->vertices[2].color = 0xffff0000;

	//device->SetRenderState(
	//	D3DRS_LIGHTING,	//라이팅모드	
	//	FALSE			//꺼버려라
	//);
}

void GameMain::Destroy()
{
	SceneManager::GetInstance()->Destroy();
}

void GameMain::Update()
{
	SceneManager::GetInstance()->Update();
	/*setMap();
	if (PtInRect(&rcTile->GetRect(), Mouse::GetInstance()->GetPosition()))
	{
		save();
	} */
}

void GameMain::Render()
{
	/*device->SetFVF(MYVERTEX::FVF);

	device->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		1,
		this->vertices,
		sizeof(MYVERTEX)
	);
*/
	SceneManager::GetInstance()->Render();
	/*_sprite->Render();
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_animation->SetCoord({ m_tiles[i].rc->GetCoord() });
		_animation->Update({ m_tiles[i].terrainFrameX, m_tiles[i].terrainFrameY });
		_animation->Render();
		if (m_tiles[i].obj == OBJ_NONE) continue;

		_animation->SetCoord({ m_tiles[i].rc->GetCoord() });
		_animation->Update({ m_tiles[i].objFrameX, m_tiles[i].objFrameY });
		_animation->Render();

	}
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		m_tiles[i].rc->Render();
	}
	for (int i = 0; i < SAMPLETILEY *SAMPLETILEX; i++)
	{
		m_sampleTile[i].rcTile->Render();

	}
	rcTile->Render();*/
}

void GameMain::maptoolSetup()
{
	ctrSelect = CTRL_TERRAINDRAW;

	
	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);
	//오른쪽셋팅
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			m_sampleTile[i * SAMPLETILEX + j].terrainFrameX = j;
			m_sampleTile[i * SAMPLETILEX + j].terrainFrameY = i;

			m_sampleTile[i * SAMPLETILEX + j].rcTile =
				new Rect(device, { (float)(viewport.Width - TILESIZEX + j *TILESIZE),
				(float)(i * TILESIZE) }, { (float)TILESIZE,(float)TILESIZE });
			m_sampleTile[i * TILEX + j].rcTile->Initialize();

		}
	}

	//왼쪽 셋팅
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{

			m_tiles[i * TILEX + j].rc =
				new Rect(device, { (float)(j * TILESIZE),
				(float)(i * TILESIZE) }, { (float)TILESIZE,(float)TILESIZE });
			m_tiles[i * TILEX + j].rc->Initialize();
		}
	}

	//처음에 깔려있는 타일
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		m_tiles[i].terrainFrameX = 2;
		m_tiles[i].terrainFrameY = 0;

		m_tiles[i].objFrameX = 0;
		m_tiles[i].objFrameY = 0;

		m_tiles[i].terrain = terrainSelect(m_tiles[i].terrainFrameX, m_tiles[i].terrainFrameY);
		m_tiles[i].obj = OBJ_NONE;
	}
}

void GameMain::setMap()
{
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&m_sampleTile[i].rcTile->GetRect(),Mouse::GetInstance()->GetPosition()))
		{
			if (Mouse::GetInstance()->ButtonDown(0))
			{
				m_currentTile.x = m_sampleTile[i].terrainFrameX;
				m_currentTile.y = m_sampleTile[i].terrainFrameY;
				break;

			}
		}
	}

	//왼쪽 맵
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&m_tiles[i].rc->GetRect(), Mouse::GetInstance()->GetPosition()))
		{
			if (Mouse::GetInstance()->ButtonPress(0))
			{
				if (ctrSelect == CTRL_TERRAINDRAW)
				{
					m_tiles[i].terrainFrameX = m_currentTile.x;
					m_tiles[i].terrainFrameY = m_currentTile.y;

					m_tiles[i].terrain = terrainSelect(m_currentTile.x, m_currentTile.y);
				}

				else if (ctrSelect == CTRL_OBJDRAW)
				{
					m_tiles[i].objFrameX = m_currentTile.x;
					m_tiles[i].objFrameY = m_currentTile.y;

					m_tiles[i].obj = objSelect(m_currentTile.x, m_currentTile.y);
				}

				else if (ctrSelect == CTRL_ERASER)
				{
					m_tiles[i].objFrameX = 0;
					m_tiles[i].objFrameY = 0;

					//m_tiles[i].terrainFrameX = 19;
					//m_tiles[i].terrainFrameY = 7;

					m_tiles[i].obj = OBJ_NONE;
					m_tiles[i].terrain = TR_END;
				}
				break;
			}
		}
	}
}

void GameMain::save()
{
	HANDLE file;
	DWORD write;
	file = CreateFile(L"tileMap.map",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	WriteFile(file, m_tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	WriteFile(file, m_pos, sizeof(int) * 2, &write, NULL);
	CloseHandle(file);
}

void GameMain::load()
{
	HANDLE file;
	DWORD read;
	file = CreateFile(L"tileMap.map",
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(file, m_tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, m_pos, sizeof(int) * 2, &read, NULL);
	CloseHandle(file);
}

TERRAIN GameMain::terrainSelect(int frameX, int frameY)
{
	//시멘트
	if (frameX == 1 && frameY == 0)
	{
		return TR_CEMENT;
	}

	//흙
	else if (frameX == 2 && frameY == 0)
	{
		return TR_GROUND;
	}

	//잔디
	else if (frameX == 3 && frameY == 0)
	{
		return TR_GRASS;
	}

	//물
	else if (frameX == 4 && frameY == 0)
	{
		return TR_WATER;
	}

	return TR_GRASS;
}

OBJECT GameMain::objSelect(int frameX, int frameY)
{
	//탱크1
	if (frameX == 0 && frameY == 0)
	{
		return OBJ_TANK1;
	}

	//탱크2
	else if (frameX == 19 && frameY == 7)
	{
		return OBJ_TANK2;
	}

	//블록1방짜리
	else if (frameX == 0 && frameY == 1)
	{
		return OBJ_BLOCK1;
	}

	//블록3방짜리
	else if (frameX == 17 && frameY == 2)
	{
		return OBJ_BLOCK2;
	}

	//안깨지는 블록
	else if (frameX == 12 && frameY == 3)
	{
		return OBJ_BLOCK3;
	}

	return OBJ_BLOCK3;
}
