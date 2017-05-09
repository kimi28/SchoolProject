#pragma once
class DrawImage;
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void AddImage(DrawImage* drawImage);
	void ReDraw(DrawImage* drawImage, int number);


};

