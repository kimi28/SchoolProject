#pragma once
#include "DrawImage.h"

class DrawImage;
class SceneManager
{
private:
	int width;
	int height;
	int x;
	int y;
	int posX;
	int posY;
	int Width;
	int Height;
	int Npc_posX;
	int Npc_posY;
public:
	SceneManager();
	~SceneManager();

	Gdiplus::Rect rectNpc = { Npc_posX, Npc_posY, Width, Height };
	Gdiplus::Rect rect = { posX, posY, Width, Height };

	void MoveUp(DrawImage* drawImage, SceneManager* sceneManager, int number);
	void MoveDown(DrawImage* drawImage, SceneManager* sceneManager, int number);
	void MoveRight(DrawImage* drawImage, SceneManager* sceneManager, int number);
	void MoveLeft(DrawImage* drawImage, SceneManager* sceneManager, int number);
	void SetPosition(DrawImage* drawImage);
	void AddImage(DrawImage* drawImage);
	void ReDraw(DrawImage* drawImage, int number);
};