#pragma once
#include "DrawImage.h"
#define WIDTH 40
#define HEIGHT 60


class DrawImage;
class SceneManager
{
private:
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

	Gdiplus::Rect rectNpc;
	Gdiplus::Rect rect;

	bool CheckCollision();

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