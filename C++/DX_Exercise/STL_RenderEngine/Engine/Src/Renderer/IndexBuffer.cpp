#include "Core.h"
#include "IndexBuffer.h"
#include "Util/STLException.h"

namespace Ronnie
{
	IndexBuffer::IndexBuffer()
		: BufferBase()
	{
	}

	IndexBuffer::~IndexBuffer()
	{
	}

	void IndexBuffer::Initialize(ID3D11Device* device, void* data, size_t count, uint32 byteWidth)
	{
		// reinterpret_cast: ������ ���� ��ȯ(��������).
		// dynamic_cast: ��� ������ �ִ� ������ ��ȯ.
		// RTTI: Runtime-Type Information.
		// GetPlayerPawn() -> APawn* -> AMyPawn*
		// TryGetPawnOwner() -> APawn* -> ���� ���̺�.
		// static_cast -> int->float. float->int. __int64 -> int.
		this->count = static_cast<uint32>(count);
		this->byteWidth = byteWidth;

		// ���� ����.
		D3D11_BUFFER_DESC indexBufferDesc = { 0 };
		indexBufferDesc.ByteWidth = sizeof(uint32) * this->count;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

		// ���� ������ ����.
		D3D11_SUBRESOURCE_DATA indexData = { 0 };
		indexData.pSysMem = data;

		// ����.
		HRESULT hr = device->CreateBuffer(
			&indexBufferDesc,
			&indexData,
			&buffer
		);

		ThrowIfFailed(hr, "Failed to create index buffer.");
	}

	void IndexBuffer::Bind(ID3D11DeviceContext* context)
	{
		context->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0);
	}

	void IndexBuffer::Draw(ID3D11DeviceContext* context)
	{
		context->DrawIndexed(count, 0, 0);
	}
}