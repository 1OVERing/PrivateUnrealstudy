#include "Core.h"
#include "ConstantBuffer.h"
#include "Util/STLException.h"

namespace Ronnie
{
	ConstantBuffer::ConstantBuffer()
		: BufferBase()
	{
	}

	ConstantBuffer::~ConstantBuffer()
	{
	}

	void ConstantBuffer::Initialize(
		ID3D11Device* device, 
		void* data, 
		size_t count, 
		uint32 byteWidth)
	{
		// 필요한 정보 저장.
		this->count = static_cast<uint32>(count);
		this->byteWidth = byteWidth;

		// 상수 버퍼 생성.
		D3D11_BUFFER_DESC bufferDesc = { 0 };
		bufferDesc.ByteWidth = byteWidth;
		//bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		// 버퍼 데이터.
		D3D11_SUBRESOURCE_DATA bufferData = { 0 };
		bufferData.pSysMem = data;

		// 버퍼 생성.
		auto result 
			= device->CreateBuffer(&bufferDesc, &bufferData, &buffer);

		// 예외 처리.
		ThrowIfFailed(result, "Failed to create constatnt buffer.");
	}

	void ConstantBuffer::Update(ID3D11DeviceContext* context, void* data)
	{
		// 데이터 변경 작업.
		// 1.락(Lock) -> 2.데이터 설정 -> 3.락 해제.
		D3D11_MAPPED_SUBRESOURCE mappedResource = { 0 };
		// 락(Map).
		context->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		// 메모리 복사.
		memcpy(mappedResource.pData, data, byteWidth);
		// 언락(Unmap)
		context->Unmap(buffer, 0);

		//context->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
	}

	void ConstantBuffer::VSBind(ID3D11DeviceContext* context, uint32 index)
	{
		context->VSSetConstantBuffers(index, 1, &buffer);
	}

	void ConstantBuffer::PSBind(ID3D11DeviceContext* context, uint32 index)
	{
		context->PSSetConstantBuffers(index, 1, &buffer);
	}

	void ConstantBuffer::Bind(ID3D11DeviceContext* context)
	{
	}
}