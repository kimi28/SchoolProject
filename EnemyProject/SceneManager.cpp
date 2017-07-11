#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"

SceneManager* SceneManager::instance = NULL;
Scene* SceneManager::currentScene =NULL;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	
}

SceneManager * SceneManager::GetInstance()
{
	if (instance == NULL)
		instance = new SceneManager();
	return instance;
}

void SceneManager::DeleteInstance()
{
	SAFE_DELETE(instance);
}

void SceneManager::Initialize()
{
}

void SceneManager::Destroy()
{
	map<char*, Scene*> ::iterator iter = mSceneList.begin();
	if (iter->second != NULL) {
		if (iter->second == currentScene) iter->second->Destroy();
		SAFE_DELETE(iter->second);
		iter = mSceneList.erase(iter);
	}
	else {
		iter++;
	}
	mSceneList.clear();
}

void SceneManager::Update()
{
	if (currentScene) currentScene->Update();
}

void SceneManager::Render()
{
	if (currentScene)currentScene->Render();
}

void SceneManager::AddScene(char * sceneName, Scene * scene)
{
	if (scene) {
		mSceneList.insert(make_pair(sceneName, scene));
	}
}

void SceneManager::ChangeScene(char * sceneName)
{
	map<char*, Scene*>::iterator find = mSceneList.find(sceneName);
	assert(find != mSceneList.end());
	assert(find->second != currentScene);

	find->second->Initaialize();

	if (currentScene) currentScene->Destroy();
	currentScene = find->second;
}
