#pragma once

#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex_vc.lib")

using namespace FMOD;

#define EXTRACHANNELBUFFER 5
#define SOUNDBUFFER 20

#define TOTALSOUNDBUFFER EXTRACHANNELBUFFER + SOUNDBUFFER

class SoundManager
{
public:
	static SoundManager* GetInstance();
	static void DeleteInstance();

	void Initialize();
	void Destroy();
	void Update();
	void Render();

	void AddSound(char* keyName, char* soundName, bool bgm = FALSE, bool loop = FALSE);

	void Play(char* keyName, float volum = 1.0f);
	void Stop(char* keyName);
	void Pause(char* keyName);
	void Resume(char* keyName);

	bool IsPlay(char* keyName);
	bool IsPause(char* keyName);

private:
	SoundManager();
	~SoundManager();

	static SoundManager* instance;

	map<char*, Sound**> soundList;

	System* system;
	Sound** sound;
	Channel** channel;

	bool isPlay;
	bool isPause;
	
};

