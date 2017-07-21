#include "stdafx.h"
#include "Timer.h"

Timer* Timer::instance = NULL;

Timer * Timer::GetInstance()
{
	if (instance == NULL) {
		instance = new Timer;
	}
	return instance;
}

void Timer::DeleteInstance()
{
	SAFE_DELETE(instance);
}

void Timer::Tick(float lockFPS)
{
	if (isHardwaer) {
		QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
		timeScale = 1 / periodFrequency;
	}
	else {
		curTime = timeGetTime();
		timeScale = 0.0001f;
	}

	timeElapsed = (curTime - lastTime)* timeScale;

	if (lockFPS > 0.0f) {
		while (timeElapsed < (1.0f / lockFPS)) {
			if (isHardwaer)
				QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
			else
				curTime = timeGetTime();

			timeElapsed = (curTime - lastTime)* timeScale;
		}
	}

	lastTime = curTime;
	FPSFrameCount++;
	FPStimeElapsed += timeElapsed;
	worldTime += timeElapsed;

	if (FPStimeElapsed > 0.1f) {
		frameRate = FPSFrameCount;

		FPSFrameCount = 0;
		FPStimeElapsed = 0.0f;
	}
}

void Timer::Initialize()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency)) {
		isHardwaer = true;

		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
	}
	else {
		isHardwaer = false;

		lastTime = timeGetTime();
	}

	frameRate = 0;
	FPSFrameCount = 0;
	FPStimeElapsed = 0.0f;
	worldTime = 0.0f;
}

void Timer::Render()
{
	WCHAR str[255];
	swprintf(str, L"FPS: %d", frameRate);
	PrintText::GetInstance()->AddText(str);
}

Timer::Timer()
{

}

Timer::~Timer()
{
}