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
		// �ʿ��� ���� ����.
		this->count = static_cast<uint32>(count);
		this->byteWidth = byteWidth;

		// ����.
		D3D11_BUFFER_DESC desc = { 0 };
		desc.ByteWidth = byteWidth * this->count;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.Usage = D3D11_USAGE_DEFAULT;

		// ������ ����.
		D3D11_SUBRESOURCE_DATA vertexData = { 0 };
		vertexData.pSysMem = data;

		HRESULT hr = device->CreateBuffer(
			&desc, &vertexData, &buffer
		);

		// ���� ó��.
		ThrowIfFailed(hr, "Failed to create vertex buffer");
	}

	void VertexBuffer::Bind(ID3D11DeviceContext* context)
	{
		// ���� �ϳ��� ����Ʈ ũ��.
		const uint32 stride = byteWidth;

		// ���� �����͸� ó�� �о�� �ϴ� �ε��� ��.
		const uint32 offset = 0;

		// ���ε�(����/�Ҵ�).
		context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
	}
	
	void VertexBuffer::Draw(ID3D11DeviceContext* context)
	{
		context->Draw(count, 0);
	}
}