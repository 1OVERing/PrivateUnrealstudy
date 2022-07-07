// 정점 쉐이더 출력.
struct ps_input
{
	float4 position : SV_Position;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL; // 법선 벡터.
};

Texture2D baseMap : register(t0);
Texture2D colorMap : register(t1);
SamplerState samplerState : register(s0);

float4 main(ps_input input) : SV_TARGET
{
	float4 baseMapColor = baseMap.Sample(samplerState, input.texCoord);
	float4 colorMapColor = colorMap.Sample(samplerState, input.texCoord);
	
	float4 blendColor = saturate(baseMapColor * colorMapColor);
	return blendColor;
}