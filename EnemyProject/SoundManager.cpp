#include "stdafx.h"
#include "SoundManager.h"

SoundManager* SoundManager::instance = NULL;

SoundManager::SoundManager()
	: system(NULL)
	, channel(NULL)
	, sound(NULL)
{
}


SoundManager::~SoundManager()
{
}

SoundManager * SoundManager::GetInstance()
{
	if (instance == NULL){
		instance = new SoundManager();
	}
	return instance;
}

void SoundManager::DeleteInstance()
{
	SAFE_DELETE(instance);
}

void SoundManager::Initialize()
{
	System_Create(&system);

	system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	sound = new Sound*[TOTALSOUNDBUFFER];
	channel = new Channel *[TOTALSOUNDBUFFER];

	memset(sound, 0, sizeof(Sound*) * TOTALSOUNDBUFFER);
	memset(channel, 0, sizeof(Channel*) * TOTALSOUNDBUFFER);

}

void SoundManager::Destroy()
{
	if (channel != NULL || sound != NULL) {
		for (int i = 0; i < TOTALSOUNDBUFFER; i++) {
			if (channel != NULL) {
				if (channel[i]) channel[i]->stop();
			}
			if (sound != NULL) {
				if (sound[i]) sound[i]->release();
			}
		}
	}
	SAFE_DELETE(channel);
	SAFE_DELETE(sound);

	if (system != NULL) {
		system->release();
		system->close();
	}
}

void SoundManager::Update()
{
	system->update();
}

void SoundManager::Render()
{
}

void SoundManager::AddSound(char * keyName, char * soundName, bool bgm, bool loop)
{
	if (loop) {
		if (bgm) {
			system->createStream(soundName, FMOD_LOOP_NORMAL, 0, &sound[soundList.size()]);
		}
		else {
			system->createSound(soundName, FMOD_LOOP_NORMAL, 0, &sound[soundList.size()]);
		}
	}
	else {
		system->createSound(soundName, FMOD_DEFAULT, 0, &sound[soundList.size()]);
	}

	soundList.insert(make_pair(keyName, &sound[soundList.size()]));
}
//0.0f~1.0f;
void SoundManager::Play(char * keyName, float volum)
{
	int count = 0;
	auto iter = soundList.begin();
	for (iter; iter != soundList.end(); ++iter, count++) {
		if (keyName == iter->first) {
			system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &channel[count]);

			channel[count]->setVolume(volum);
		}
	}
}

void SoundManager::Stop(char * keyName)
{
	int count = 0;
	auto iter = soundList.begin();
	for (iter; iter != soundList.end(); ++iter, count++) {
		if (keyName == iter->first) {
			channel[count]->stop();
			break;
		}
	}
}

void SoundManager::Pause(char * keyName)
{
	int count = 0;
	auto iter = soundList.begin();
	for (iter; iter != soundList.end(); ++iter, count++) {
		if (keyName == iter->first) {
			channel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::Resume(char * keyName)
{
	int count = 0;
	auto iter = soundList.begin();
	for (iter; iter != soundList.end(); ++iter, count++) {
		if (keyName == iter->first) {
			channel[count]->setPaused(false);
			break;
		}
	}
}

bool SoundManager::IsPlay(char * keyName)
{
	int count = 0;
	auto iter = soundList.begin();
	for (iter; iter != soundList.end(); ++iter, count++) {
		if (keyName == iter->first) {
			channel[count]->isPlaying(&isPlay);
			break;
		}
	}
	return isPlay;
}

bool SoundManager::IsPause(char * keyName)
{
	int count = 0;
	auto iter = soundList.begin();
	for (iter; iter != soundList.end(); ++iter, count++) {
		if (keyName == iter->first) {
			channel[count]->isPlaying(&isPause);
			break;
		}
	}
	return isPause;
}
