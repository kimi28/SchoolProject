#pragma once
#define ROW_SIZE 20
#define COLUMN_SIZE 10
#define BLOCK_SIZE 30

class Rect;
class Map
{
public:
	Map(LPDIRECT3DDEVICE9 device);
	~Map();
	
	void Initialize();
	void Destroy();
	void Update();
	void UpdateMoveDown(const DWORD &currTime);
	void UpdateMoveLeft(const DWORD &currTime);
	void UPdateMoveRight(const DWORD &currTime);
	void UpdateRotateBlock(const DWORD &currTime);
	void UpdateKeyStatus();
	void Render();

	void GenerateNewBlock();
	void MoveDown(int blockID);
	void MoveLeft(int blockID);
	void MoveRight(int blockID);

	void RotateBlock(int blockID);
	void ClearBlock();

private:
	LPDIRECT3DDEVICE9 device;
	DWORD lastMoveTime;
	DWORD lastLeftRightTime;

	int array[ROW_SIZE][COLUMN_SIZE];

	int number;
	bool isDownKey;
	bool isLeftKey;
	bool isRightKey;
	bool isUpKey;

	int currentBlockCenterX;
	int currentBlockCenterY;

};

