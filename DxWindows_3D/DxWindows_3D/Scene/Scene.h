#pragma once

class Scene
{

public:
	Scene();
	~Scene();

	//�⺻�Լ��� �߻��Լ���
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update(float timeDelta) = 0;
	virtual void Render() = 0;
};

