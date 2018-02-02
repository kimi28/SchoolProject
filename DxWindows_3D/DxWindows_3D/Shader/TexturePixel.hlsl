
//colorPixel.hlsl

Texture2D tMap;		//���� �ؽ�ó
SamplerState samp;	//��������

struct PixelInput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD0;
};

float4 TexturePixelShader(PixelInput input) : SV_TARGET
{
	float4 diffuse = tMap.Sample(samp, input.uv);

	return diffuse;
}