// 픽셀 쉐이더 입력.
struct ps_input
{
	float4 position : SV_Position;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL; // 법선 벡터.
	float3 worldPosition : TEXCOORD1;
	float3 cameraDirection : TEXCOORD2;
};

// 조명 정보 (상수버퍼).
cbuffer Light : register(b0)
{
	float3 lightPosition;
	float positionPadding;
	
	float3 diffuseColor;
	float diffusePadding;
	
	float3 ambientColor;
	float ambientPower;
	
	float3 specularColor;
	float specularPower;
};

Texture2D map : register(t0);
SamplerState mapSampler : register(s0);

float4 main(ps_input input) : SV_TARGET
{
	// 색상 추출.
	float4 mapColor = map.Sample(mapSampler, input.texCoord);

	// 입사광 벡터.
	float3 lightDirection = normalize(-lightPosition); // 벡터 크기 1로 만들기.

	// 노멀 벡터.
	float3 worldNormal = normalize(input.normal);

	// !! 쉐이더에서 어떤 계산을 할 때는 항상 같은 공간에서 해야함.
	// 내적 연산
	//float NdotL = saturate(dot(worldNormal, -lightDirection));
	float NdotL = dot(worldNormal, -lightDirection);
	
	float3 reflection = reflect(-lightDirection, worldNormal);
	float3 cameraDirection = normalize(input.cameraDirection);
	float RdotV = 0;
	
	// 스페큘러(정반사) 계산.
	if (NdotL > 0)
	{	
		RdotV = saturate(dot(reflection, cameraDirection));
		RdotV = pow(RdotV, specularPower);
	}
	
	NdotL = pow(NdotL * 0.5f + 0.5f, 2.0f);			// half lambert.

	float3 diffuse = diffuseColor * NdotL * mapColor.rgb;
	float3 ambient = ambientColor * ambientPower * mapColor.rgb;
	float3 specular = specularColor * RdotV * mapColor.rgb;
	
	return float4(diffuse + ambient + specular, 1);
}