#pragma once

class Scene_02 : public Scene
{
public:
	Scene_02(LPDIRECT3DDEVICE9 device);
	~Scene_02();

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

