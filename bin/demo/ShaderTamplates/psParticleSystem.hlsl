
struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
	float opacityFactor : TEXCOORD1;
	float linearDepth : TEXCOORD2;
};


Texture2D color;
SamplerState samp
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

struct PS_OUT
{
	float4 color : SV_TARGET0;
	float4 linDepth : SV_TARGET1;
};

PS_OUT main(VS_OUT input)
{

	PS_OUT output = (PS_OUT)0;
	
	float4 s = color.Sample(samp,input.uv);
	s.w *= input.opacityFactor;

	output.color = s;
	output.linDepth = input.linearDepth;
	return output;
}