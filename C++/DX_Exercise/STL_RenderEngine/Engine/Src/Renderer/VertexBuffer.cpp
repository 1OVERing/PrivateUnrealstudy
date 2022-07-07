#include "Core.h"
#include "VertexBuffer.h"
#include "Util/STLException.h"

namespace Ronnie
{
	VertexBuffer::VertexBuffer()
		: BufferBase()
	{
	}

	VertexBuffer::~VertexBuffer()
	{
	}

	void VertexBuffer::Initialize(ID3D11Device* device, void* data, size_t count, uint32 byteWidth)
	{
		// 필요한 변수 저장.
		this->count = static_cast<uint32>(count);
		this->byteWidth = byteWidth;

		// 생성.
		D3D11_BUFFER_DESC desc = { 0 };
		desc.ByteWidth = byteWidth * this->count;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.Usage = D3D11_USAGE_DEFAULT;

		// 데이터 설정.
		D3D11_SUBRESOURCE_DATA vertexData = { 0 };
		vertexData.pSysMem = data;

		HRESULT hr = device->CreateBuffer(
			&desc, &vertexData, &buffer
		);

		// 예외 처리.
		ThrowIfFailed(hr, "Failed to create vertex buffer");
	}

	void VertexBuffer::Bind(ID3D11DeviceContext* context)
	{
		// 정점 하나의 바이트 크기.
		const uint32 stride = byteWidth;

		// 정점 데이터를 처음 읽어야 하는 인덱스 값.
		const uint32 offset = 0;

		// 바인딩(연결/할당).
		context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
	}
	
	void VertexBuffer::Draw(ID3D11DeviceContext* context)
	{
		context->Draw(count, 0);
	}
}