// 정점 쉐이더 입력 구조체.
struct vs_input
{
	// float3: x,y,z.
	float3 pos : POSITION;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL; // 법선 벡터.
};

// 정점 쉐이더 출력.
struct vs_output
{
	float4 position : SV_Position;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL; // 법선 벡터.
};

// 상수 버퍼.
// 바이트 정렬이 필요함(16 바이트 정렬).
cbuffer Transform : register(b0)
{
	matrix world;
};

// 카메라의 뷰행렬/투영행렬/위치 전달하는 상수버퍼.
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