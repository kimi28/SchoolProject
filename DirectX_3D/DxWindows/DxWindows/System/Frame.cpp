#include "../stdafx.h"
#include "Frame.h"
#include <stdio.h>

#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")

Frame::Frame(void)
{
}


Frame::~Frame(void)
{
}

HRESULT Frame::Init(void)
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&preriodTime))
	{
		bHardware = true;
		timeScaleSec = 1.0f / preriodTime;

		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
	}
	else
	{
		bHardware = false;
		lastTime = timeGetTime();

		timeScaleSec = 1.0f / 1000.0f;
	}

	totalSec = 0.0f;
	frameCountSec = 0.0f;
	framePerSec = 0;
	frameCount = 0;

	return S_OK;
}

void Frame::Release(void)
{
}

void Frame::UpdateTime(float frameLock)
{
	if (bHardware)
		QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
	else
		curTime = timeGetTime();

	deltaTime = curTime - lastTime;

	frameDeltaSec = deltaTime * timeScaleSec;

	if (frameLock > 0.0f)
	{
		float lockTime = (1.0f / frameLock);

		while (frameDeltaSec < lockTime)
		{
			if (bHardware)
				QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
			else
				curTime = timeGetTime();

			deltaTime = curTime - lastTime;

			frameDeltaSec = deltaTime * timeScaleSec;
		}
	}

	lastTime = curTime;

	totalSec += frameDeltaSec;

	if (frameCountSec >= 1.0f)
	{
		framePerSec = frameCount;
		frameCount = 0;
		frameCountSec -= 1.0f;
	}
	frameCount++;
}

void Frame::DrawTimeInfo(HDC hdc)
{
}

void Frame::DrawShadowText(HDC hdc, int x, int y, char * szText, COLORREF textColor)
{
}
