// �ȼ� ���̴� �Է�.
struct ps_input
{
	float4 position : SV_Position;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL; // ���� ����.
	float3 worldPosition : TEXCOORD1;
	float3 cameraDirection : TEXCOORD2;
	float3 binormal : TEXCOORD3;
	float3 tangent : TEXCOORD4;
};

// ���� ���� (�������).
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
	// ��ָ� �� ����.
	float3 tangentNormal = normalmap.Sample(mapSampler, input.texCoord).rgb;
	
	// ���� �� ����.
	tangentNormal = tangentNormal * 2 - 1;
	
	// ź��Ʈ ���� -> ���� ���� ��ȯ ��� ���� (TBN).
	float3x3 TBN = float3x3(
		normalize(input.tangent),
		normalize(input.binormal),
		normalize(input.normal)
	);
	
	// ���� ����.
	float4 diffusemapColor = diffusemap.Sample(mapSampler, input.texCoord);

	// �Ի籤 ����.
	float3 lightDirection = normalize(-lightPosition); // ���� ũ�� 1�� �����.

	// ��� ����.
	//float3 worldNormal = normalize(input.normal);
	float3 worldNormal = mul(tangentNormal, TBN);

	// !! ���̴����� � ����� �� ���� �׻� ���� �������� �ؾ���.
	// ���� ����
	//float NdotL = saturate(dot(worldNormal, -lightDirection));
	float NdotL = dot(worldNormal, -lightDirection);
	
	float3 reflection = reflect(-lightDirection, worldNormal);
	float3 cameraDirection = normalize(input.cameraDirection);
	float RdotV = 0;
	
	// ����ŧ��(���ݻ�) ���.
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