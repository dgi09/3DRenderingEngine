struct VS_OUT 
{
	float4 pos : SV_POSITION;
	float2 uv :TEXCOORD;
};

Texture2D hdr : register(t0);
Texture2D bloomTexture : register(t1);

SamplerState Samp
{
	Filter = MIN_MAG_MIP_POINT;
	AddressU = WRAP;
	AddressV = WRAP;
};

SamplerState LinSamp
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

float4 main(VS_OUT input) : SV_TARGET
{
	float3 inColor =  hdr.Sample(Samp,input.uv).rgb;
	float3 bloom = bloomTexture.Sample(LinSamp,input.uv).rgb;
	inColor += bloom;

	float3 x = max(0,inColor - 0.004);
    float3 retColor = (x*(6.2*x+.5))/(x*(6.2*x+1.7)+0.06);
    return float4(retColor,1);
}