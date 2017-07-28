#pragma once

class Scene;
class SceneManager
{
public:
	static SceneManager* GetInstance();
	static void DeleteInstance();

	void Initalize();
	void Destroy();
	void Update();
	void Render();

	void AddScene(char* sceneName, Scene* scene);
	void changeScene(char* sceneName);

private:
	 map<char*, Scene*> mSceneList;
	 map<char*, Scene*>::iterator miSenceList;

	static SceneManager* instance;
	static Scene* currentScene;

	


	SceneManager();
	~SceneManager();
};

