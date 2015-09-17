
struct VS_IN
{
	float3 pos : POSITION;
	float2 uv : TEXCOORD;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
	float opacityFactor : TEXCOORD1;
	float linearDepth : TEXCOORD2;
};

struct ParticleData
{
	float3 worldPos;
	float size;
	float opacityFactor;
	float padd1;
	float padd2;
	float padd3;
};

#define MAX_PARTICLES 100

cbuffer Camera
{
	matrix view;
	matrix projection;
};

cbuffer CameraVectors
{
	float3 camUpVector;
	float padding1;
	float3 camRightVector;
	
	float padding2;
};

cbuffer Data
{
	ParticleData particlesData[MAX_PARTICLES];
};

VS_OUT main( VS_IN input,uint instanceID : SV_InstanceID,uint vI : SV_VertexID)
{
	
	switch(vI)
	{
	case 0:
		input.pos = -camUpVector - camRightVector;
		break;
	case 1:
		input.pos = camUpVector - camRightVector;
		break;
	case 2:
		input.pos = camRightVector - camUpVector;
		break;
	case 3:
		input.pos = camUpVector + camRightVector;
		break;
	default:
		break;
	}

	float3 worldPos = particlesData[instanceID].worldPos;
	float size = particlesData[instanceID].size;

	float3 wPos = input.pos * size + worldPos;
	
	VS_OUT output = (VS_OUT)0;

	output.pos = mul(mul(float4(wPos,1.0f),view),projection);
	output.uv = input.uv;
	output.opacityFactor = particlesData[instanceID].opacityFactor;
	output.linearDepth = output.pos.z / output.pos.w;

	return output;
}