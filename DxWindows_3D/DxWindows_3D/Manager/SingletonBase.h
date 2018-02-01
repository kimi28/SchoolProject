#pragma once
template<typename T>
class SingletonBase
{
protected:
	static T* instance;

protected:
	SingletonBase() {};
	~SingletonBase() {};
public:
	//인스턴스 얻기
	static T* GetInstance();
	static void ReleaseInstance();
};

template<typename T>
T* SingletonBase<T>::instance = NULL;

template<typename T>
T* SingletonBase<T>::GetInstance()
{
	if (instance == NULL)
		instance = new T;

	return instance;
}

template<typename T>
void SingletonBase<T>::ReleaseInstance()
{
	if (instance)
	{
		delete instance;
		instance = NULL;
		//SAFE_DELETE(instance);
	}
}

