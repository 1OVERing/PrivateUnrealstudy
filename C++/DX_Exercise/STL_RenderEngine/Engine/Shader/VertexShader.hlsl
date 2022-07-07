// 정점 쉐이더 입력 구조체.
struct vs_input
{
	// float3: x,y,z.
	float3 pos : POSITION;
	//float3 color : COLOR;
	float2 texCoord : TEXCOORD;
};

// 정점 쉐이더 출력.
struct vs_output
{
	float4 position : SV_Position;
	//float3 color : COLOR;
	float2 texCoord : TEXCOORD;
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
	
	// X,Y,Z축의 위치 -> Vector(벡터).
	// 벡터: 방향/크기(길이).
	// w: 1 -> 점. w: 0 -> 벡터.
	output.position = float4(input.pos, 1.0f);
	
	// 공간 변환.
	// 로컬 -> 월드.
	// 벡터(행렬) x 행렬. 1x4
	output.position = mul(output.position, world);
	// 월드 -> 뷰공간.
	output.position = mul(output.position, view);
	// 뷰공간 -> 투영공간.
	output.position = mul(output.position, projection);
	
	//output.color = input.color;
	output.texCoord = input.texCoord;
	
	return output;
}

// 정점쉐이더 진입점(Entry Point). 메인 함수.
//float4 main( float3 pos : POSITION ) : SV_POSITION
//{
//	return float4(pos, 1);
//}