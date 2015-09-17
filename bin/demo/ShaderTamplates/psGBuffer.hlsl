#define MATERIAL

#ifdef MATERIAL
Texture2D diffuse_map;
Texture2D bump_map;

SamplerState WrapSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};


cbuffer MaterialData
{
	float4 diffuseColor;
	uint specPspecIemmisivePad;
	uint matOptions;
	uint padding1;
	uint padding2;
};
#endif

struct PS_INPUT
{
	float4 pos:SV_POSITION;
	float3 normal:NORMAL;
	float3 tangent:TANGENT;
	float2 uv:TEXCOORD;
};


struct PS_OUTPUT
{
	float4 diffuseColor : SV_TARGET0;
	float4 normal : SV_TARGET1;
	float4 specular : SV_TARGET2;
};

PS_OUTPUT main(PS_INPUT input)
{
	PS_OUTPUT output = (PS_OUTPUT)0;

	float4 texelColor;

#ifdef BUMPMAPPING
	float4 bumpColor = bump_map.Sample(bump_sampler,input.uv);
	bumpColor = (2.0f * bumpColor) - 1.0f;

	float3 biTangent = cross(input.normal,input.tangent);
	float3x3 tangentSpace = float3x3(input.tangent,biTangent,input.normal);
	input.normal = mul(input.normal,(float3)bumpColor);
#endif

	if(matOptions & 1 == 1)
	{
		texelColor = diffuse_map.Sample(WrapSampler,input.uv);
		texelColor = pow(texelColor,2.2);// gamma correction
	}
	else texelColor = diffuseColor;

	output.diffuseColor = texelColor;	

	output.specular.x = (float)(specPspecIemmisivePad & 0x000000FF) / 256.0f;
	output.specular.y = (float)((specPspecIemmisivePad & 0x0000FF00) >> 8) / 256.0f;
	output.specular.z = (float)((specPspecIemmisivePad & 0x00FF0000) >> 16) / 256.0f;
	output.specular.w = 0.0f;

	

#ifdef ILLUMINATION
	output.normal.xyz = float3(input.normal.xyz * 0.5 + 0.5);
	output.specular.w = 1.0f;
#endif

	
	return output;
}