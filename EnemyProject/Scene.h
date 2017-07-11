#pragma once
class Scene
{
public:
	Scene(LPDIRECT3DDEVICE9 device);
	~Scene();

	virtual void Initialize() = 0;
	virtual void Destroy() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	LPDIRECT3DDEVICE9 device;

};

