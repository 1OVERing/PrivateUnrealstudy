// 픽셀 쉐이더 입력.
struct ps_input
{
	float4 position : SV_Position;
	//float3 color : COLOR;
	float2 texCoord : TEXCOORD;
};

Texture2D map : register(t0);
SamplerState mapSampler : register(s0);

float4 main(ps_input input) : SV_TARGET
{
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);
	//return float4(input.color.r, input.color.g, input.color.b, 1);
	
	// 색상 추출.
	float4 mapColor = map.Sample(mapSampler, input.texCoord);
	
	//return float4(input.color, 1);
	//return mapColor * float4(input.color, 1);
	return mapColor;
}