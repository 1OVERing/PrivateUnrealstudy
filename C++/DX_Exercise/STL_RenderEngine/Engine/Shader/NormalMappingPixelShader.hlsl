// 픽셀 쉐이더 입력.
struct ps_input
{
	float4 position : SV_Position;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL; // 법선 벡터.
	float3 worldPosition : TEXCOORD1;
	float3 cameraDirection : TEXCOORD2;
	float3 binormal : TEXCOORD3;
	float3 tangent : TEXCOORD4;
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

Texture2D diffusemap : register(t0);
Texture2D normalmap : register(t1);
SamplerState mapSampler : register(s0);

float4 main(ps_input input) : SV_TARGET
{
	// 노멀맵 값 추출.
	float3 tangentNormal = normalmap.Sample(mapSampler, input.texCoord).rgb;
	
	// 원래 값 복원.
	tangentNormal = tangentNormal * 2 - 1;
	
	// 탄젠트 공간 -> 월드 공간 변환 행렬 생성 (TBN).
	float3x3 TBN = float3x3(
		normalize(input.tangent),
		normalize(input.binormal),
		normalize(input.normal)
	);
	
	// 색상 추출.
	float4 diffusemapColor = diffusemap.Sample(mapSampler, input.texCoord);

	// 입사광 벡터.
	float3 lightDirection = normalize(-lightPosition); // 벡터 크기 1로 만들기.

	// 노멀 벡터.
	//float3 worldNormal = normalize(input.normal);
	float3 worldNormal = mul(tangentNormal, TBN);

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

	float3 diffuse = diffuseColor * NdotL * diffusemapColor.rgb;
	float3 ambient = ambientColor * ambientPower * diffusemapColor.rgb;
	float3 specular = specularColor * RdotV * diffusemapColor.rgb;
	
	return float4(diffuse + ambient + specular, 1);
}