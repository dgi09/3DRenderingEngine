#ifdef DIFFUSE_MAP

Texture2D diffuse_map;
SamplerState diffuse_sampler;

#endif

#ifdef ILLUMINATION

#define MAX_DIR_LIGHTS 5
#define MAX_POINT_LIGHTS 20

	struct DirLight
	{
		float4 diffuseColor;
		float3 direction;
		float padding;
	};

	struct PointLight
	{
		float4 diffuseColor;
		float3 position;
		float rangeRCP;
	};

	cbuffer GlobalAmbiantBuffer
	{
		float4 globalAmbiant;
	};

	cbuffer IlluminationInfo
	{
		float3 cameraPosition;
		uint numOfActivDirLights;
		uint numOfActivePointLights;
		float padding1;
	};

	cbuffer DirectionalLights
	{
		DirLight dirLights[MAX_DIR_LIGHTS];
	};

	cbuffer PointLights
	{
		PointLight pointLights[MAX_POINT_LIGHTS];
	};

	float4 GetDirLightColor(DirLight light,float3 normal,float3 vertPos)
	{
		float3 invDir = normalize(-light.direction);
		float intensity = saturate(dot(invDir,normal));
		float4 final = light.diffuseColor * intensity;

		float3 toEye = normalize(cameraPosition - vertPos);
		float3 halfWay = toEye + invDir;
		float specFactor = saturate(dot(halfWay,normal));
		final += light.diffuseColor * pow(specFactor,100);

		return final;
	}

	float4 GetPointLightColor(PointLight light,float3 normal,float3 vertPos)
	{

		float3 invDir = normalize(light.position - vertPos);

		float intensity = saturate(dot(invDir,normal));
		float4 final = light.diffuseColor * intensity;

		float3 toEye = normalize(cameraPosition - vertPos);
		float3 halfWay = toEye + invDir;
		float specFactor = saturate(dot(halfWay,normal));
		final += light.diffuseColor * pow(specFactor,100);

		float dirL = length(invDir);
		float dtlNorm = 1.0 - saturate(dirL * light.rangeRCP);
		float att = dtlNorm * dtlNorm;
		
		return final * att;
	}

#endif

struct PS_INPUT
{
	float4 pos:SV_POSITION;
	float3 normal:NORMAL;
	float3 tangent:TANGENT;
	float2 uv:TEXCOORD;

#ifdef ILLUMINATION
	float3 vertPos:POSITION0;
#endif

};

#ifdef BUMPMAPPING
	Texture2D bump_map;
	SamplerState bump_sampler; 
#endif


float4 main(PS_INPUT psIn) : SV_TARGET
{
	float4 finalColor;
	float4 texelColor;

#ifdef DIFFUSE_MAP
	
	texelColor = diffuse_map.Sample(diffuse_sampler,psIn.uv);
#else 
	texelColor = float4(1.0f,0.0f,0.0f,1.0f);
#endif

#ifdef BUMPMAPPING
	float4 bumpColor = bump_map.Sample(bump_sampler,psIn.uv);
	bumpColor = (2.0f * bumpColor) - 1.0f;

	float3 biTangent = cross(psIn.normal,psIn.tangent);
	float3x3 tangentSpace = float3x3(psIn.tangent,biTangent,psIn.normal);
	psIn.normal = normalize(mul(psIn.normal,(float3)bumpColor));
#endif


#ifdef ILLUMINATION
	float4 lights = globalAmbiant;
	

	for(int i = 0;i < numOfActivDirLights;i++)
	{
		lights += GetDirLightColor(dirLights[i],psIn.normal,psIn.vertPos);
	}
	
	
	for(int j = 0;j < numOfActivePointLights;j++)
	{
		lights += GetPointLightColor(pointLights[j],psIn.normal,psIn.vertPos);
	}

	finalColor = texelColor * saturate(lights);
	
#else 
	finalColor = texelColor;
#endif

	return finalColor;
}