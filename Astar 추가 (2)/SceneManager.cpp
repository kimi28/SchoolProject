#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"


SceneManager* SceneManager::instance = NULL;
Scene* SceneManager::currentScene = NULL;
SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

SceneManager * SceneManager::GetInstance()
{
	if (instance == NULL)
		instance = new SceneManager;
	return instance;
}

void SceneManager::DeleteInstance()
{
	SAFE_DELETE(instance);
}

void SceneManager::Initalize()
{
	
}

void SceneManager::Destroy()
{
	map<char*, Scene*>::iterator iter  = mSceneList.begin();
	for (iter; iter != mSceneList.end();)
	{
		//»èÁ¦
		if (iter->second != NULL)
		{
			if (iter->second == currentScene) iter->second->Destroy();
			SAFE_DELETE(iter->second);
			iter = mSceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	mSceneList.clear();
}

void SceneManager::Update()
{
	if (currentScene) currentScene->Update();

}

void SceneManager::Render()
{
	if (currentScene) currentScene->Render();
}

void SceneManager::AddScene(char * sceneName, Scene * scene)
{
	if (scene)
	{
		mSceneList.insert(make_pair(sceneName, scene));
	}

}

void SceneManager::changeScene(char * sceneName)
{
	miSenceList = mSceneList.find(sceneName);

	assert(miSenceList != mSceneList.end());
	assert(miSenceList->second != currentScene);

	miSenceList->second->Initialize();

	if (currentScene) currentScene->Destroy();
	currentScene = miSenceList->second;

}
