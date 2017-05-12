#pragma once
#include "DrawImage.h"

class DrawImage;
class SceneManager
{
private:
	Gdiplus::Rect rect;

	int backgroudWidth;
	int backgroudHeight;
	int backgroudX;
	int backgroudY;
	int characterX;
	int characterY;
	int npcX;
	int npcY;
public:
	SceneManager();
	~SceneManager();

	bool isCollision();

	void MoveUp(DrawImage* drawImage, int number);
	void MoveDown(DrawImage* drawImage, int number);
	void MoveRight(DrawImage* drawImage, int number);
	void MoveLeft(DrawImage* drawImage, int number);
	void SetPosition(DrawImage* drawImage);
	void SetPositionDungeon(DrawImage* drawImage);
	void AddImage(DrawImage* drawImage);
	void ReDraw(DrawImage* drawImage, int number);
	void ReDrawDungeon(DrawImage* drawImage, int number);
};