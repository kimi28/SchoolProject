
//ColorVertexShader

//외부에 인자값 전역변수

cbuffer MatrixBuffer
{
	matrix world;		//월드 행렬
	matrix view;		//뷰 행렬
	matrix projection;	//투영 행렬
};

struct VertexInput
{
	float4 position : POSITION0;
	float2 uv		: TEXCOORD0;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD0;
};

PixelInput TextureVertexShader(VertexInput input)
{
	PixelInput output;
	input.position.w = 1.0f;

	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);
	
	output.uv = input.uv;

	return output;
}