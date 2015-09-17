
struct PS_INPUT
{
	float4 pos:SV_POSITION;
	float2 uv :TEXCOORD;
};

PS_INPUT main( float3 pos : POSITION , float2 uv : TEXCOORD )
{
	PS_INPUT output;
	output.pos = float4(pos,1.0f);
	output.uv = uv;
	return output;
}