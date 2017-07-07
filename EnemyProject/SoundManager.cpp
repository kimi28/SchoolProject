#include "stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

SoundManager * SoundManager::GetInstance()
{
	return nullptr;
}

void SoundManager::DeleteInstance()
{
}

void SoundManager::Initialize()
{
}

void SoundManager::Destroy()
{
}

void SoundManager::Update()
{
}

void SoundManager::Render()
{
}

void SoundManager::AddSound(char * keyName, char * soundName, bool bgm, bool loof)
{
}

void SoundManager::Play(char * keyName, float volum)
{
}

void SoundManager::Stop(char * keyName)
{
}

void SoundManager::Pause(char * keyName)
{
}

void SoundManager::Resume(char * keyName)
{
}

bool SoundManager::IsPlay(char * keyName)
{
	return false;
}

bool SoundManager::IsPause(char * keyName)
{
	return false;
}
