struct VS_OUT 
{
	float4 pos : SV_POSITION;
	float2 uv :TEXCOORD;
};

Texture2D inTexture;

SamplerState Samp
{
	Filter = MIN_MAG_MIP_BILINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

float4 main(VS_OUT input) : SV_TARGET
{
	return inTexture.Sample(Samp,input.uv);
}