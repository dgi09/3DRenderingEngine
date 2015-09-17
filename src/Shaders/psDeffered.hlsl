struct PS_INPUT
{
	float4 pos:SV_POSITION;
	float2 uv :TEXCOORD;
};

SamplerState gBufferSampler 
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

SamplerState pointSamp
{
	Filter = MIN_MAG_MIP_POINT;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

Texture2D diffuseMap;
Texture2D normalMap;
Texture2D specularMap;
Texture2D depthMap;

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

cbuffer ViewProjBuffer
{
	matrix viewProjInverse;
};

float4 GetDirLightColor(DirLight light,float3 normal,float3 vertPos,uint specInt,uint specPower)
{
	float3 invDir = normalize(-light.direction);
	float intensity = saturate(dot(invDir,normal));
	float4 final = light.diffuseColor * intensity;

	float3 toEye = normalize(cameraPosition - vertPos);
	float3 halfWay = toEye + invDir;
	float specFactor = saturate(dot(halfWay,normal));
	final += light.diffuseColor * pow(specFactor,specPower) * specInt;

	return final;
}

float4 GetPointLightColor(PointLight light,float3 normal,float3 vertPos,uint specInt,uint specPower)
{
	float3 dir = light.position - vertPos;

	float3 invDir = normalize(dir);

	float intensity = saturate(dot(invDir,normal));
	float4 final = light.diffuseColor * intensity;

	float3 toEye = normalize(cameraPosition - vertPos);
	float3 halfWay = normalize(toEye + invDir);
	float specFactor = saturate(dot(halfWay,normal));
	final += light.diffuseColor * pow(specFactor,specPower) * specInt;

	float dirL = length(dir);
	float dtlNorm = 1.0f - saturate(dirL * light.rangeRCP);
	float att = dtlNorm * dtlNorm;

	return final * att;
}

float3 GetWorldPos(float2 uv,float depth)
{
	
	float4 projSpace = float4(uv.x * 2.0f - 1.0f,(1.0f - uv.y)*2.0f - 1.0f,depth,1.0f);
	float4 worldSpace = mul(projSpace,viewProjInverse);
	return worldSpace.xyz/worldSpace.w;
}

float4 main(PS_INPUT input) : SV_TARGET
{

		float4 finalColor;

		float4 diffuseColor = diffuseMap.Sample(gBufferSampler,input.uv);
		float4 specularSample = specularMap.Sample(gBufferSampler,input.uv);

		float depth = depthMap.Sample(pointSamp,input.uv).r;

	    if(depth != 1.0f)
		{
			uint emmisive = 256 * specularSample.z;
			diffuseColor *= emmisive;

			if(specularSample.w == 1.0f)
			{

				float4 normalSample = normalMap.Sample(gBufferSampler,input.uv);
				float3 normal = float3(normalSample.xyz * 2.0 - 1.0);
			

				float3 vPos = GetWorldPos(input.uv,depth);//positionsMap.Sample(gBufferSampler,input.uv).xyz;

				float4 lights = globalAmbiant;
			
				uint specIntensity = 256 * specularSample.x;
				uint specPower = 256 * specularSample.y;

				for(unsigned int i = 0;i < numOfActivDirLights;i++)
				{
					lights += GetDirLightColor(dirLights[i],normal,vPos,specIntensity,specPower);
				}
	
		
				for(unsigned int j = 0;j < numOfActivePointLights;j++)
				{
					lights += GetPointLightColor(pointLights[j],normal,vPos,specIntensity,specPower);
				}

				finalColor = diffuseColor * lights;
			}
			else finalColor = diffuseColor;

		}
		else finalColor = diffuseColor;
		
		return finalColor;
	
}