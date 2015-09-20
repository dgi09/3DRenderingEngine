struct VS_OUT 
{
	float4 pos : SV_POSITION;
	float2 uv :TEXCOORD;
};

Texture2D nonTransperant;
Texture2D particles;
Texture2D ntDepth;
Texture2D particlesDepth;

SamplerState Samp
{
	Filter = MIN_MAG_MIP_POINT;
	AddressU = WRAP;
	AddressV = WRAP;
};

float4 main(VS_OUT input) : SV_TARGET
{
	float3 nonTranspColor = nonTransperant.Sample(Samp,input.uv).rgb;
	float4 particlesColor = particles.Sample(Samp,input.uv);

	float ntD = ntDepth.Sample(Samp,input.uv).r;
	float partD = particlesDepth.Sample(Samp,input.uv).r;

	float3 color;
	if(partD < ntD)
	{
		color = particlesColor.rgb * particlesColor.a + nonTranspColor * (1.0f - particlesColor.a);
	}
	else 
	{
		color = nonTranspColor;
	}

	color = pow(color,1/2.2);

	return float4(color,1.0f);
}