// ���� ���̴� �Է� ����ü.
struct vs_input
{
	// float3: x,y,z.
	float3 pos : POSITION;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL; // ���� ����.
};

// ���� ���̴� ���.
struct vs_output
{
	float4 position : SV_Position;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL; // ���� ����.
};

// ��� ����.
// ����Ʈ ������ �ʿ���(16 ����Ʈ ����).
cbuffer Transform : register(b0)
{
	matrix world;
};

// ī�޶��� �����/�������/��ġ �����ϴ� �������.
cbuffer Camera : register(b1)
{
	matrix view;
	matrix projection;
	float3 position;
	float padding;
};

vs_output main(vs_input input)
{
	vs_output output;
	
	output.position = mul(float4(input.pos, 1), world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);
	
	output.texCoord = input.texCoord;
	output.normal = mul(input.normal, (float3x3) world);
	
	return output;
}