
Texture2D<float4> hdr;
RWTexture2D<float4> res;

[numthreads(10, 10, 1)]
void main( uint3 pos : SV_DispatchThreadID )
{
	float3 hdrIn = hdr.Load(int3(pos.xy,0)).rgb ;
	float3 lumFactors = float3(0.2126f,0.7152f,0.0722f);

	float minLum = 2.0f;
	float curLum = dot(lumFactors,hdrIn);
	
	if(curLum > minLum)
	{
		float treshhold = 0.9f;
		float3 remove = hdrIn * treshhold;
		res[pos.xy] = float4(hdrIn - remove,1.0f);
	}
	else
	res[pos.xy] = float4(0,0,0,1);

}