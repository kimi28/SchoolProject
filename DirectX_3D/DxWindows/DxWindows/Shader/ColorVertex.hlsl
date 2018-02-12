

cbuffer MatrixBuffer
{
	matrix world;
	matrix view;
	matrix projection;
};

struct VertexInput
{
	float4 position : POSITION0;
	float4 color :	COLOR0;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR0;
};

PixelInput ColorVertexShader(VertexInput input)
{
	PixelInput output;

	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

	output.color = input.color;

	return output;
}