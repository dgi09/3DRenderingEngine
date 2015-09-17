Texture2D<float4> input;
RWTexture2D<float4> output;


[numthreads(10, 10, 1)]
void main( uint3 pos : SV_DispatchThreadID )
{
	int pixels[13] = {-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6};
	float weights[13] = {
0.002216,
0.008764,
0.026995,
0.064759,
0.120985,
0.176033,
0.199471,
0.176033,
0.120985,
0.064759,
0.026995,
0.008764,
0.002216,
};

	float3 color = float3(0,0,0);
    
	[unroll]
    for(int i = 0;i < 13;i++)
	{
		color += input.Load(int3(pos.xy + int2(pixels[i],0),0)).xyz * weights[i];
	}


	output[pos.xy] = float4(color,1.0f);
}