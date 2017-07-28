#include"stdafx.h"
#include "Timer.h"

Timer* Timer::instance = NULL;

Timer::Timer()
{
	Initialize();
}


Timer::~Timer()
{
}

Timer * Timer::GetInstance()
{
	if (instance == NULL)
		instance = new Timer();

	return instance;
}

void Timer::DeleteInstance()
{
	SAFE_DELETE(instance);
}
void Timer::SetDevice(LPDIRECT3DDEVICE9 device)
{
	this->device = device;
}

void Timer::Initialize()
{

	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		//64��Ʈ ������ ����� �� �ֵ��� ������ ������
		//����ũ�μ����带 (1/1000000)�� ���� �����Ͽ� ���� ��Ȯ�� �ð����� �����ϱ� ����
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		//�ʴ� �ð� ��� ����
		_timeScale = 1.0000f / _periodFrequency;
	}

	else
	{
		_isHardware = false;
		//�и������� ������ �ð����� �ʴ� 1000�� ī��Ʈ
		_lastTime = timeGetTime();
		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPStimeElapsed = 0.0f;
	_worldTime = 0.0f;


}

void Timer::Render()
{

	WCHAR str[255];
	swprintf(str, L"fps : %d", _frameRate);
	PrintText::GetInstance()->AddText(str);

	swprintf(str, L"worldTime : %d", this->getWorldTime());
	PrintText::GetInstance()->AddText(str);

	swprintf(str, L"fps : %d", this->getElapsedTime());
	PrintText::GetInstance()->AddText(str);
}

void Timer::tick(float lockFPS)
{
	//���� Ÿ�̸Ӹ� �����Ѵٸ�
	if (_isHardware)
	{
		//�� ���� ����ũ���� ������ ����Ѵ�.(1/1000000)
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		//�������� ������ time�Լ��� �̿� �и�������(1/1000)
		_curTime = timeGetTime();
	}

	//������ �ð��� ����ð��� �����
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	if (lockFPS > 0.0f)
	{
		//���� �������� �ð��� �����ҋ����� �������Ѷ�
		while (_timeElapsed < (1.0f / lockFPS))
		{
			if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else _curTime = timeGetTime();

			//������ �ð��� ����ð��� �����
			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;	//������ �ð��� ���
	_FPSFrameCount++;		//�ڵ����� ������ ī��Ʈ ����
	_FPStimeElapsed += _timeElapsed;	//�ʴ� ������ �ð� ����� ����
	_worldTime += _timeElapsed;	//��ü �ð� ����� ����

								//������ �ʱ�ȭ�� 1�ʸ��� ����
	if (_FPStimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPStimeElapsed = 0.0f;
	}

}

unsigned long Timer::getFrameRate(WCHAR * str) const
{
	if (str != NULL)
	{
		wsprintf(str, L"FPS: %d", _frameRate);
	}
	return _frameRate;
}
