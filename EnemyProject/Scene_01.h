#pragma once

class Scene_01 : public Scene
{
public:
	Scene_01(LPDIRECT3DDEVICE9 device);
	~Scene_01();

	void Initialize() override;
	void Destroy() override;
	void Update() override;
	void Render() override;

private:
	LPD3DXLINE line;
	float posY;
	D3DXVECTOR3 lineVector[360];

	D3DXMATRIX world;

	SYSTEMTIME time;
};

