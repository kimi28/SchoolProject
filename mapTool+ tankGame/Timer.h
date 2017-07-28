#pragma once
class Timer
{
public:
	Timer();
	~Timer();

	static Timer * GetInstance();
	static void DeleteInstance();

	void SetDevice(LPDIRECT3DDEVICE9 device);

	//���� �ð� ���
	void tick(float lockFPS = 0.0f);
	//���� FPS ��������
	unsigned long getFrameRate(WCHAR* str = nullptr) const;
	//�������Ӵ� ��� �ð�
	float getElapsedTime() const { return _timeElapsed; }
	//��ü ��� �ð� ��������
	float getWorldTime() const { return _worldTime; }


	void Initialize();
	void Destroy();
	void Update();
	void Render();

private:

	LPDIRECT3DDEVICE9 device;


	static Timer* instance;

	bool _isHardware;	//���� Ÿ�̸Ӹ� �����ϳ�?
	float _timeScale;	//�ð� �����
	float _timeElapsed;	//�� �����Ӵ� �����
	__int64 _curTime;	//����ð�
	__int64 _lastTime;	//�������ð�
	__int64 _periodFrequency;	//�ð� �ֱ�

	unsigned long _frameRate;	//FPS
	unsigned long _FPSFrameCount;	//FPS ī��Ʈ
	float _FPStimeElapsed;		//FPS �������ð��� ���� �ð��� �����
	float _worldTime;	//��ü �ð� �����
};

