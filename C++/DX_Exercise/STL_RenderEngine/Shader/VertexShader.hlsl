// ���� ���̴� �Է� ����ü.
struct vs_input
{
	// float3: x,y,z.
	float3 pos : POSITION;
	//float3 color : COLOR;
	float2 texCoord : TEXCOORD;
};

// ���� ���̴� ���.
struct vs_output
{
	float4 position : SV_Position;
	//float3 color : COLOR;
	float2 texCoord : TEXCOORD;
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
	
	// X,Y,Z���� ��ġ -> Vector(����).
	// ����: ����/ũ��(����).
	// w: 1 -> ��. w: 0 -> ����.
	output.position = float4(input.pos, 1.0f);
	
	// ���� ��ȯ.
	// ���� -> ����.
	// ����(���) x ���. 1x4
	output.position = mul(output.position, world);
	// ���� -> �����.
	output.position = mul(output.position, view);
	// ����� -> ��������.
	output.position = mul(output.position, projection);
	
	//output.color = input.color;
	output.texCoord = input.texCoord;
	
	return output;
}

// �������̴� ������(Entry Point). ���� �Լ�.
//float4 main( float3 pos : POSITION ) : SV_POSITION
//{
//	return float4(pos, 1);
//}