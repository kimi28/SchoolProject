#pragma once
#include "DrawImage.h"
#include "Vector2D.h"

class SceneManager
{
protected:
	DrawImage* drawImage;
	Gdiplus::Rect rect;

	
public:
	SceneManager();
	~SceneManager();

	int backgroudWidth;
	int backgroudHeight;
	int backgroudX;
	int backgroudY;
	int characterX;
	int characterY;
	int npcX;
	int npcY;
	bool isCollision(Vector2D direction);

	void MoveUp(int number);
	void MoveDown(int number);
	void MoveRight(int number);
	void MoveLeft(int number);
	void SetPosition();
	void SetPositionDungeon();
	void AddImage();
	void ReDraw(int number);
	void ReDrawDungeon(int number);
	void Update();
};