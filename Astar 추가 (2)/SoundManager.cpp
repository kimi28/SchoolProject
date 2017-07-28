#include"stdafx.h"
#include "soundManager.h"

soundManager* soundManager::instance = NULL;

soundManager * soundManager::GetInstance()
{
	if (instance == NULL)
		instance = new soundManager;

	return instance;
}

void soundManager::DeleteInstance()
{
	SAFE_DELETE(instance);
}
soundManager::soundManager()
	: system(nullptr)
	, channel(nullptr)
	, sound(nullptr)
{
}

soundManager::~soundManager()
{
}

HRESULT soundManager::init()
{
	//���� �ý��� ����
	System_Create(&system);

	mi_sounds = m_sounds.begin();

	//���� ä�μ� ����
	system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//���� ä�� �����Ҵ�
	sound = new Sound *[TOTALSOUNDBUFFER];
	channel = new Channel *[TOTALSOUNDBUFFER];

	memset(sound, 0, sizeof(Sound*)* (TOTALSOUNDBUFFER));
	memset(channel, 0, sizeof(Channel*)* (TOTALSOUNDBUFFER));

	return S_OK;
}

void soundManager::release()
{
	if (channel != nullptr || sound != nullptr)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (channel != nullptr)
			{
				if (channel[i]) channel[i]->stop();
			}

			if (sound != nullptr)
			{
				if (sound[i]) sound[i]->release();
			}
		}
	}

	SAFE_DELETE(channel);
	SAFE_DELETE(sound);

	//�ý��� �ݱ�
	if (system != nullptr)
	{
		system->release();
		system->close();
	}
}

void soundManager::update()
{
	/*
	���� �ý����� ��� ������Ʈ ����� ������ �ٲ�ų�
	����� ���� ���带 ä�ο��� ������ �� �پ��� �۾��� �ڵ����� ���ش�.
	*/
	//���ΰ��ӿ��� ���� �Ŵ����� ������Ʈ ���ش�.
	system->update();
}

void soundManager::render()
{
}

void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)
	{
		if (bgm)
		{
			system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, nullptr, &sound[m_sounds.size()]);
		}

		else
		{
			system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, nullptr, &sound[m_sounds.size()]);
		}
	}
	else
	{
		system->createStream(soundName.c_str(), FMOD_DEFAULT, nullptr, &sound[m_sounds.size()]);
	}

	//�ʿ� ���带 Ű���� �Բ� ����ش�.
	m_sounds.insert(make_pair(keyName, &sound[m_sounds.size()]));
}

void soundManager::play(string keyName, float volume)
{
	int count = 0;
	
	for (mi_sounds; mi_sounds != m_sounds.end(); ++mi_sounds, count++)
	{
		if (keyName == mi_sounds->first)
		{
			//���� �÷���
			system->playSound(FMOD_CHANNEL_FREE, *mi_sounds->second, false, &channel[count]);
			//��������
			channel[count]->setVolume(volume);
		}
	}
}

void soundManager::stop(string keyName)
{
	int count = 0;
	
	for (mi_sounds; mi_sounds != m_sounds.end(); ++mi_sounds, count++)
	{
		if (keyName == mi_sounds->first)
		{
			channel[count]->stop();
			break;
		}
	}
}

void soundManager::pause(string keyName)
{
	int count = 0;
	for (mi_sounds; mi_sounds != m_sounds.end(); ++mi_sounds, count++)
	{
		if (keyName == mi_sounds->first)
		{
			channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	int count = 0;
	for (mi_sounds; mi_sounds != m_sounds.end(); ++mi_sounds, count++)
	{
		if (keyName == mi_sounds->first)
		{
			channel[count]->setPaused(false);
			break;
		}
	}
}

bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;
	int count = 0;
	for (mi_sounds; mi_sounds != m_sounds.end(); ++mi_sounds, count++)
	{
		if (keyName == mi_sounds->first)
		{
			channel[count]->isPlaying(&isPlay);
			break;
		}
	}
	return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	int count = 0;
	for (mi_sounds; mi_sounds != m_sounds.end(); ++mi_sounds, count++)
	{
		if (keyName == mi_sounds->first)
		{
			channel[count]->getPaused(&isPause);
			break;
		}
	}
	return isPause;
}
