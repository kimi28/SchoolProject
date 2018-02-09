
//TexturePixel.hlsl

Texture2D _map; //실제 텍스처
SamplerState samp; //색상정보

struct PixelInput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD0;
};

float4 TexturePixelShader(PixelInput input) : SV_TARGET
{
	float4 diffuse = _map.Sample(samp,input.uv);

	return diffuse;
}