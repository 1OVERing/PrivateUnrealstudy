// ���� ���̴� �Է� ����ü.
struct vs_input
{
	// float3: x,y,z.
	float3 pos : POSITION;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL;			// ���� ����.
};

// ���� ���̴� ���.
struct vs_output
{
	float4 position : SV_Position;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL;			// ���� ����.
	float3 worldPosition : TEXCOORD1;
	float3 cameraDirection : TEXCOORD2;
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
	float3 cameraPosition;
	float padding;
};

vs_output main(vs_input input)
{
	vs_output output;

	// X,Y,Z���� ��ġ -> Vector(����).
	// ����: ����/ũ��(����).
	// w: 1 -> ��. w: 0 -> ����.
	output.position = float4(input.pos, 1.0f);

	// ���� ��ȯ.
	// ���� -> ����.
	// ����(���) x ���. 1x4
	output.position = mul(output.position, world);

	output.worldPosition = output.position.xyz;

	// ���� -> �����.
	output.position = mul(output.position, view);
	// ����� -> ��������.
	output.position = mul(output.position, projection);

	output.texCoord = input.texCoord;

	// ��ֵ� ���� ��ȯ.
	output.normal = mul(input.normal, (float3x3)world);
	
	output.cameraDirection = normalize(output.worldPosition - cameraPosition);

	return output;
}