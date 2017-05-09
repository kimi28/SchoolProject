#include "SceneManager.h"
#include "DrawImage.h"
#include <conio.h>

void main() {

	SceneManager* sceneManager = new SceneManager();
	DrawImage* drawImage = new DrawImage();

	sceneManager->AddImage(drawImage);

	int width = drawImage->GetClientArea().right;
	int height = drawImage->GetClientArea().bottom;
	int x = 0;
	int y = 0;
	int posX = width / 2;
	int posY = height / 2;
	int Width = 40;
	int Height = 60;
	int number = 1;

	drawImage->SetPosition(0, Gdiplus::Rect(x, y, width, height));

	for (int i = 1; i < (int)drawImage->GetImageCount(); i++)
	{
		drawImage->SetPosition(i, posX, posY);
	}

	Sleep(1000);

	sceneManager->ReDraw(drawImage, 2);

	Gdiplus::Rect rect;
	rect = { posX, posY, Width, Height };

	while (true) {
		char key = getch();

		switch (key) {
		case 'w':
			if (number > 3) {
				number = 1;
			}
			if (posY > y) {
				rect = drawImage->GetPosition(number + 3);
				rect.X = posX;
				rect.Y = posY - 20;
				drawImage->SetPosition(number + 3, rect.X, rect.Y);
				sceneManager->ReDraw(drawImage, number + 3);
				posX = rect.X;
				posY = rect.Y;
			}
			else {
				rect = drawImage->GetPosition(number + 3);
				drawImage->SetPosition(number + 3, posX, posY);
				sceneManager->ReDraw(drawImage, number + 3);
			}
			number++;
			break;
		case 's':
			if (number > 3) {
				number = 1;
			}
			if (posY < (height - Height)) {
				rect = drawImage->GetPosition(number);
				rect.X = posX;
				rect.Y = posY + 20;
				drawImage->SetPosition(number, rect.X, rect.Y);
				sceneManager->ReDraw(drawImage, number);
				posX = rect.X;
				posY = rect.Y;
			}
			else {
				rect = drawImage->GetPosition(number);
				drawImage->SetPosition(number, posX, posY);
				sceneManager->ReDraw(drawImage, number);
			}
			number++;
			break;
		case 'a':
			if (number > 3) {
				number = 1;
			}
			if (posX > x) {
				rect = drawImage->GetPosition(number + 9);
				rect.X = posX - 20;
				rect.Y = posY;
				drawImage->SetPosition(number + 9, rect.X, rect.Y);
				sceneManager->ReDraw(drawImage, number + 9);
				posX = rect.X;
				posY = rect.Y;

			}
			else {
				rect = drawImage->GetPosition(number + 9);
				drawImage->SetPosition(number + 9, posX, posY);
				sceneManager->ReDraw(drawImage, number + 9);
			}
			number++;
			break;
		case 'd':
			if (number > 3) {
				number = 1;
			}
			if (posX < (width - Width)) {
				rect = drawImage->GetPosition(number + 6);
				rect.X = posX + 20;
				rect.Y = posY;
				drawImage->SetPosition(number + 6, rect.X, rect.Y);
				sceneManager->ReDraw(drawImage, number + 6);
				posX = rect.X;
				posY = rect.Y;
			}
			else {
				rect = drawImage->GetPosition(number + 6);
				drawImage->SetPosition(number + 6, posX, posY);
				sceneManager->ReDraw(drawImage, number + 6);
			}
			number++;
			break;

		}
	}

	delete drawImage;
	delete sceneManager;
}