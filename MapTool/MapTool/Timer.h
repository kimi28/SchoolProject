#pragma once
class Timer
{
public:

	static Timer* GetInstance();
	static void DeleteInstance();

	void Tick(float lockFPS = 0.0f);

	void Initialize();
	void Render();

private:
	static Timer* instance;

	bool isHardwaer;
	float timeScale;
	float timeElapsed;
	__int64 curTime;
	__int64 lastTime;
	__int64 periodFrequency;


	unsigned long frameRate;
	unsigned long FPSFrameCount;
	float FPStimeElapsed;
	float worldTime;


	Timer();
	~Timer();


};

