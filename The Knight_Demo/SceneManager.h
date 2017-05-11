#pragma once
#include "DrawImage.h"
#define WIDTH 40
#define HEIGHT 60


class DrawImage;
class SceneManager
{
private:
	int mapWidth;
	int mapHeight;
	int mapX;
	int mapY;
	int characterX;
	int characterY;
	int npcX;
	int npcY;
public:
	SceneManager();
	~SceneManager();

	Gdiplus::Rect rectNpc = { npcX, npcY, WIDTH, HEIGHT };
	Gdiplus::Rect rect = { characterX, characterY, WIDTH, HEIGHT };

	void MoveUp(DrawImage* drawImage, SceneManager* sceneManager, int number);
	void MoveDown(DrawImage* drawImage, SceneManager* sceneManager, int number);
	void MoveRight(DrawImage* drawImage, SceneManager* sceneManager, int number);
	void MoveLeft(DrawImage* drawImage, SceneManager* sceneManager, int number);
	void SetPosition(DrawImage* drawImage);
	void AddImage(DrawImage* drawImage);
	void ReDraw(DrawImage* drawImage, int number);
	void ReDrawDungeon(DrawImage* drawImage, int number);
};