#pragma once
#include "../Manager/SingletonBase.h"

class Frame : public SingletonBase<Frame>
{
private:
	bool			m_bHardWare;		//������ Ÿ�̸� ���� ����

	__int64			m_nPreriodTime;		//1�ʿ� ���ī��Ʈ �ϴ°�?
	__int64			m_nLastTime;		//������ ������ �ð�
	__int64			m_nCurTime;			//���� �ð�
	__int64			m_nDeltaTime;		//���� �����Ӱ� �����ð�

	double			m_TimeScaleSec;		//1ī��Ʈ ����.
	double			m_FrameDeltaSec;	//�������� ��� ��
	double			m_TotalSec;			//���α׷� ������ ����ð�.

	double			m_FrameCountSec;	//������ ���� �ð�
	DWORD			m_FrameCount;		//������ ī��Ʈ
	DWORD			m_FramePerSec;		//�ʴ� ������

public:

	Frame(void);
	~Frame(void);

	HRESULT Init(void);
	void Release(void);

	//�ž�����Ʈ �����ش�.
	void UpdateTime(float frameLock = 0.0f);

	//Ÿ�������� ����Ѵ�
	void DrawTimeInfo(HDC hdc);

	//�����Ӱ��� ���� �ʽð��� ��´�.
	double GetFrameDeltaSec(void) { return m_FrameDeltaSec; }


	void DrawShadowText(HDC hdc, int x, int y, char* szText, COLORREF textColor);
};

#define FRAME Frame::GetInstance()