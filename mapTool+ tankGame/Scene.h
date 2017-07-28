#pragma once
class Scene
{
protected:

public:
	Scene();
	~Scene();

	virtual void Initialize() =0;
	virtual void Destroy() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;


protected:
	LPDIRECT3DDEVICE9 device;
};

