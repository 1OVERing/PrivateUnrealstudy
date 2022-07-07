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
		// reinterpret_cast: 포인터 단위 변환(막무가내).
		// dynamic_cast: 상속 구조에 있는 포인터 변환.
		// RTTI: Runtime-Type Information.
		// GetPlayerPawn() -> APawn* -> AMyPawn*
		// TryGetPawnOwner() -> APawn* -> 가상 테이블.
		// static_cast -> int->float. float->int. __int64 -> int.
		this->count = static_cast<uint32>(count);
		this->byteWidth = byteWidth;

		// 버퍼 생성.
		D3D11_BUFFER_DESC indexBufferDesc = { 0 };
		indexBufferDesc.ByteWidth = sizeof(uint32) * this->count;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

		// 버퍼 데이터 생성.
		D3D11_SUBRESOURCE_DATA indexData = { 0 };
		indexData.pSysMem = data;

		// 생성.
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