#pragma once

class Scene
{

public:
	Scene();
	~Scene();

	//기본함수를 추상함수로
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update(float timeDelta) = 0;
	virtual void Render() = 0;
};

