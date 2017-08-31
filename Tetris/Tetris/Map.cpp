#include "stdafx.h"
#include "Map.h"
#include "Rect.h"

Map::Map(LPDIRECT3DDEVICE9 device)
	: device(device)
{
	number = 0;
	isDownKey = false;
	isLeftKey = false;
	isRightKey = false;
}


Map::~Map()
{
}

void Map::Initialize()
{
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COLUMN_SIZE; j++) {
			array[i][j] = 0;
		}
	}//2차배열 초기화
	GenerateNewBlock();//block 생성

	lastMoveTime = timeGetTime();//마지막 이동한 시간
	lastLeftRightTime = timeGetTime();//마지막 좌우 이동한 시간
}

void Map::Destroy()
{
}

void Map::Update()
{
	DWORD currTime = timeGetTime();//현재 시간

	UpdateKeyStatus();//키보드 입력체크 함수 호출
	UpdateMoveDown(currTime);//block 아래로 이동하는 함수
	UpdateMoveLeft(currTime);//block 좌측으로 이동하는 함수
	UPdateMoveRight(currTime);//block 우측으로 이동하는 함수
}

void Map::UpdateMoveDown(const DWORD &currTime)
{
	int interval;
	if (isDownKey)//만약 키보드가 입력이 되었다면
		interval = 1000 / 30; // 가속//  가속된 속도로 아래로 이동한다.
	else//키보드 입력이 없으면 
		interval = 1000;//1초의 속도로 아래로 이동한다.
	if (currTime - lastMoveTime > interval) { //
		Move(number);//
		lastMoveTime = currTime;
	}
}

void Map::UpdateMoveLeft(const DWORD currTime)
{
	int interval;
	if (isLeftKey)
		interval = 1000 / 20;
	else
		return;

	if (currTime - lastLeftRightTime > interval) {
		MoveLeft(number);
		lastLeftRightTime = currTime;
	}
}

void Map::UPdateMoveRight(const DWORD currTime)
{
	int interval;
	if (isRightKey)
		interval = 1000 / 20;
	else
		return;

	if (currTime - lastLeftRightTime > interval) {
		MoveRight(number);
		lastLeftRightTime = currTime;
	}
}

void Map::UpdateKeyStatus()//키보드 입력 체크
{
	if (Keyboard::GetInstance()->KeyDown(VK_LEFT)) {
		isLeftKey = true;
	}
	else if (Keyboard::GetInstance()->KeyUp(VK_LEFT)) {
		isLeftKey = false;
	}
	else if (Keyboard::GetInstance()->KeyDown(VK_RIGHT)) {
		isRightKey = true;
	}
	else if (Keyboard::GetInstance()->KeyUp(VK_RIGHT)) {
		isRightKey = false;
	}
	else if (Keyboard::GetInstance()->KeyDown(VK_DOWN)) {
		isDownKey = true;
	}
	else if (Keyboard::GetInstance()->KeyUp(VK_DOWN)) {
		isDownKey = false;
	}
	else if (Keyboard::GetInstance()->KeyDown(VK_UP)) {

	}
}

void Map::Render()
{
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COLUMN_SIZE; j++) {
			if (array[i][j] > 0) {
				D3DXVECTOR2 coord;
				coord.x = j * BLOCK_SIZE + 100;
				coord.y = i * BLOCK_SIZE + 100;
				Rect* block = new Rect(device, coord, { BLOCK_SIZE,BLOCK_SIZE });
				block->Initialize();

				block->Render();

				block->Destroy();
				SAFE_DELETE(block);
			}
		}
	}
}

void Map::GenerateNewBlock()
{
	number++;


	int random = rand() % 5 + 1;

	if (random == 1) {
		array[0][7] = number;
		array[0][8] = number;
		array[1][8] = number;
		array[2][8] = number;

		currentBlockCenterX = 0;
		currentBlockCenterY = 8;
	}
	else if (random == 2) {
		array[0][7] = number;
		array[0][8] = number;
		array[1][7] = number;
		array[1][8] = number;

		currentBlockCenterX = -1;
		currentBlockCenterY = -1;
	}
	else if (random == 3) {
		array[0][7] = number;
		array[0][8] = number;
		array[1][8] = number;
		array[1][9] = number;

		currentBlockCenterX = 0;
		currentBlockCenterY = 8;
	}
	else if (random == 4) {
		array[0][7] = number;
		array[1][7] = number;
		array[2][7] = number;
		array[3][7] = number;

		currentBlockCenterX = 1;
		currentBlockCenterY = 7;
	}
	else if (random == 5) {
		array[0][7] = number;
		array[1][7] = number;
		array[2][7] = number;
		array[1][8] = number;

		currentBlockCenterX = 1;
		currentBlockCenterY = 7;
	}

}

void Map::Move(int blockID)
{
	// 먼저 출동체크
	bool collision = false;
	for (int i = ROW_SIZE - 1; i >= 0; i--) {
		for (int j = 0; j < COLUMN_SIZE; j++) {
			if (array[i][j] != blockID)
				continue; // 해당 블록 선택

			if (i >= ROW_SIZE - 1) // 변계 충돌
				collision = true;

			if (array[i + 1][j] != 0 && array[i + 1][j] != blockID) // 오브젝트 충돌
				collision = true;

			if (collision)
				break;
		}
		if (collision)
			break;
	}

	if (collision) {
		ClearBlock();
		GenerateNewBlock();
		return;
	}


	for (int i = ROW_SIZE - 1; i >= 0; i--) {
		for (int j = 0; j < COLUMN_SIZE; j++) {
			if (array[i][j] == blockID) {
				array[i + 1][j] = blockID;
				array[i][j] = 0;
			}
		}
	}

	if (currentBlockCenterX >= 0)
		currentBlockCenterX++;
}

void Map::MoveLeft(int blockID)
{
	bool collision = false;
	for (int i = ROW_SIZE - 1; i >= 0; i--) {
		for (int j = 0; j < COLUMN_SIZE; j++) {
			if (array[i][j] != blockID) {
				continue;
			}

			if (j <= 0)
				collision = true;

			if (array[i][j - 1] != 0 && array[i][j - 1] != blockID)
				collision = true;

			if (collision)
				break;
		}
		if (collision)
			break;
	}

	if (collision)
		return;

	for (int i = ROW_SIZE - 1; i >= 0; i--) {
		for (int j = 0; j < COLUMN_SIZE; j++) {
			if (array[i][j] == blockID) {
				array[i][j - 1] = blockID;
				array[i][j] = 0;
			}
		}
	}
	if (currentBlockCenterY >= 0)
		currentBlockCenterY--;
}

void Map::MoveRight(int blockID)
{
	bool collision = false;
	for (int i = ROW_SIZE - 1; i >= 0; i--) {
		for (int j = COLUMN_SIZE - 1; j >= 0; j--) {
			if (array[i][j] != blockID)
				continue;

			if (j >= COLUMN_SIZE - 1)
				collision = true;

			if (array[i][j + 1] != 0 && array[i][j + 1] != blockID)
				collision = true;

			if (collision)
				break;
		}
		if (collision)
			break;
	}

	if (collision)
		return;


	for (int i = ROW_SIZE - 1; i >= 0; i--) {
		for (int j = COLUMN_SIZE - 1; j >= 0; j--) {
			if (array[i][j] == blockID) {
				array[i][j + 1] = blockID;
				array[i][j] = 0;
			}
		}
	}

	if (currentBlockCenterY >= 0)
		currentBlockCenterY++;
}

void Map::RotateBlock(int blockID)
{
	if (currentBlockCenterX == -1)
		return;


	/*for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; i < COLUMN_SIZE; j++) {
			if (array[i][j] != blockID)
				continue;
			if (i == currentBlockCenterX && j == currentBlockCenterY)
				continue;


		}
	}*/
}

void Map::ClearBlock()
{
	bool checkLine = false;
	int count = 0;

	for (int i = ROW_SIZE - 1; i >= 0; i--) {

	}
}
