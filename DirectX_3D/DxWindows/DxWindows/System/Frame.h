#pragma once

class Frame : public SingletonBase<Frame>
{
	bool		bHardware;
	__int64		preriodTime;
	__int64		lastTime;
	__int64		curTime;
	__int64		deltaTime;

	double		timeScaleSec;
	double		frameDeltaSec;
	double		totalSec;
	
	double		frameCountSec;
	DWORD		frameCount;
	DWORD		framePerSec;

public:
	Frame(void);
	~Frame(void);

	HRESULT Init(void);
	void Release(void);

	void UpdateTime(float frameLock = 0.0f);

	void DrawTimeInfo(HDC hdc);

	double GetFrameDeltaSec(void) { return frameDeltaSec; }

	void DrawShadowText(HDC hdc, int x, int y, char* szText, COLORREF textColor);
};

#define FRAME Frame::GetInstance()

