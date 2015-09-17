
struct VS_OUT 
{
	float4 pos : SV_POSITION;
	float2 uv :TEXCOORD;
};

VS_OUT main( uint vI : SV_VertexID )
{
	VS_OUT o = (VS_OUT)0;
	o.uv = float2( (vI << 1) & 2, vI & 2 );
	o.pos = float4( o.uv * float2( 2.0f, -2.0f ) + float2( -1.0f, 1.0f), 0.0f, 1.0f );

	return o;
}