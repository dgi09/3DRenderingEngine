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

float A = 0.15;
float B = 0.50;
float C = 0.10;
float D = 0.20;
float E = 0.02;
float F = 0.30;
float W = 11.2;

float3 Tonemap(float3 x)
{
   return ((x*(A*x+C*B)+D*E)/(x*(A*x+B)+D*F))-E/F;
}

float4 main(VS_OUT input) : SV_TARGET
{
	float3 inColor =  hdr.Sample(Samp,input.uv).rgb;
	float3 bloom = bloomTexture.Sample(LinSamp,input.uv).rgb;
	inColor += bloom;
	//inColor *= 16.0f;

	float3 curr = Tonemap(inColor);

    float3 whiteScale = 1.0f/Tonemap(W);
    float3 color = curr*whiteScale;

    return float4(color,1);
}