#pragma once

class Scene;
class SceneManager
{
public:

	static SceneManager* GetInstance();
	static void DeleteInstance();

	void Initialize();
	void Destroy();
	void Update();
	void Render();

	void AddScene(char* sceneName, Scene* scene);
	void ChangeScene(char* sceneName);
	
private:

	map<char*, Scene*> mSceneList;

	static SceneManager* instance;
	static Scene* currentScene;

	SceneManager();
	~SceneManager();
};

