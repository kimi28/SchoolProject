
//colorPixel.hlsl

struct PixelInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR0;
};

float4 ColorPixelShader(PixelInput input) : SV_TARGET
{
	return input.color;
}