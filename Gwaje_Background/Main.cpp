#include <stdio.h>
#include <conio.h>
#include "DrawImage.h"
#include "MainCharacter.h"

void ClearAndReDraw(DrawImage* drawImage) {
	drawImage->Clear(0, 0, 0);

	for (int i = 0; i < drawImage->GetImageCount(); i++) {
		drawImage->Drawing(i);
	}

	drawImage->FlipBuffer();
}

void main() {
	DrawImage* drawImage = new DrawImage();
	drawImage->AddImage(L"resource\\Background.png");//0

	MainCharacter* mainCharacter = new MainCharacter(drawImage);

	int width = drawImage->GetClientArea().right;
	int height = drawImage->GetClientArea().bottom;
	drawImage->SetPosition(0, Gdiplus::Rect(0, 0, width, height));
	drawImage->Drawing(0);
	drawImage->FlipBuffer();
	mainCharacter->Redraw();
	Sleep(1000);
	//ClearAndReDraw(drawImage);

	Gdiplus::Rect rect;
	while (true) {
		Sleep(10);
		// 
	}
	/*while (true) {
		char key = getch();

		switch (key) {
		case 'w':
			mainCharacter->MoveUp();
			break;
		case 's':
			mainCharacter->MoveDown();
			break;
		case 'a':
			mainCharacter->MoveLeft();
			break;
		case 'd':
			mainCharacter->MoveRight();
			break;

		}
	}*/
	//사각형의 충돌
	delete drawImage;
}