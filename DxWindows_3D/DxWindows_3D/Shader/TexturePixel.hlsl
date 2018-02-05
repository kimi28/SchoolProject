
//TexturePixel.hlsl

Texture2D tMap;		//실제 텍스처
SamplerState samp;	//색상정보

struct PixelInput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD0;
};

float4 TexturePixelShader(PixelInput input) : SV_TARGET
{
	
	float4 color = tMap.Sample(samp, input.uv);
	//float4 diffuse;
	/*float distance;
	float deltaU = abs(0.5f - input.uv.x);
	float deltaV = abs(0.5f - input.uv.y);


	distance = sqrt(deltaU* deltaU + deltaV * deltaV);
	float4 color;
	*/	
	/*if (distance < 0.5f)
	{
		color = tMap.Sample(samp, input.uv);
	}
	else
	{
		color.x = 0;
		color.y = 0;
		color.z = 0;
		color.w = 1;
	}*/
	/*
	diffuse.x = color.x * 0.2f + color.y * 0.7f + color.z * 0.1f;
	diffuse.y = color.x * 0.2f + color.y * 0.7f + color.z * 0.1f;
	diffuse.z = color.x * 0.2f + color.y * 0.7f + color.z * 0.1f;

	diffuse.w = 1.0f;
	*/
	//return diffuse;
	return color;
}