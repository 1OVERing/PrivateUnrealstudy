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
		// �ʿ��� ���� ����.
		this->count = static_cast<uint32>(count);
		this->byteWidth = byteWidth;

		// ��� ���� ����.
		D3D11_BUFFER_DESC bufferDesc = { 0 };
		bufferDesc.ByteWidth = byteWidth;
		//bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		// ���� ������.
		D3D11_SUBRESOURCE_DATA bufferData = { 0 };
		bufferData.pSysMem = data;

		// ���� ����.
		auto result 
			= device->CreateBuffer(&bufferDesc, &bufferData, &buffer);

		// ���� ó��.
		ThrowIfFailed(result, "Failed to create constatnt buffer.");
	}

	void ConstantBuffer::Update(ID3D11DeviceContext* context, void* data)
	{
		// ������ ���� �۾�.
		// 1.��(Lock) -> 2.������ ���� -> 3.�� ����.
		D3D11_MAPPED_SUBRESOURCE mappedResource = { 0 };
		// ��(Map).
		context->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		// �޸� ����.
		memcpy(mappedResource.pData, data, byteWidth);
		// ���(Unmap)
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