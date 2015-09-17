#ifdef TRANSFORMATION
	cbuffer EntityTransform
	{
		matrix m_world;
	};

	cbuffer CameraTransform
	{
		matrix m_view;
		matrix m_proj;
	};

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

#ifdef SKINNING

#define MAX_BONES 50

cbuffer BONES_BUFFER
{
	matrix bones[MAX_BONES];
};

#endif

PS_INPUT main( float3 pos : POSITION ,float3 normal:NORMAL,float3 tangent:TANGENT, float2 uv:TEXCOORD
#ifdef SKINNING
			  ,float4 weights : WEIGHTS,
				uint4 boneIndex : BONES
#endif 
			)
{

	PS_INPUT ps = (PS_INPUT)0;
	ps.pos = float4(pos,1.0f);

#ifdef SKINNING
	
	matrix skin = weights.x * bones[boneIndex.x];
	skin += weights.y * bones[boneIndex.y];
	skin += weights.z * bones[boneIndex.z];
	skin += weights.w * bones[boneIndex.w];

	ps.pos = float4(pos,1.0f);
	ps.pos = mul(ps.pos,skin);
	normal = mul(normal,(float3x3)skin);
	tangent = mul(tangent,(float3x3)skin);
#endif

#ifdef TRANSFORMATION
	float4 tr = ps.pos;
	tr = mul(tr,m_world);
	tr = mul(tr,m_view);
	ps.pos = mul(tr,m_proj);

	ps.normal = normalize(mul(normal,(float3x3)m_world));
#ifdef ILLUMINATION
	ps.vertPos = mul(pos,(float3x3)m_world);
#endif
#else 
	ps.normal = normal;
	ps.tangent = tangent;
#endif


	ps.uv = uv;
	
	return ps;
}