// �ȼ� ���̴� �Է�.
struct ps_input
{
	float4 position : SV_Position;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL; // ���� ����.
	float3 worldPosition : TEXCOORD1;
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

Texture2D map : register(t0);
SamplerState mapSampler : register(s0);

float4 main(ps_input input) : SV_TARGET
{
	// ���� ����.
	float4 mapColor = map.Sample(mapSampler, input.texCoord);

	// �Ի籤 ����.
	float3 lightDirection = normalize(-lightPosition); // ���� ũ�� 1�� �����.

	// ��� ����.
	float3 worldNormal = normalize(input.normal);

	// !! ���̴����� � ����� �� ���� �׻� ���� �������� �ؾ���.
	// ���� ����
	//float NdotL = saturate(dot(worldNormal, -lightDirection));
	float NdotL = dot(worldNormal, -lightDirection);
	//NdotL = saturate(NdotL);
	NdotL = pow(NdotL * 0.5f + 0.5f, 2.0f);		// Half Lambert.

	float3 diffuse = diffuseColor * NdotL * mapColor.rgb;
	float3 ambient = ambientColor * ambientPower * mapColor.rgb;
	
	return float4(diffuse + ambient, 1);
}