#pragma once

#ifndef _BUFFER_BASE_
#define _BUFFER_BASE_

#include "Core.h"

namespace Ronnie
{
	class ENGINE_API BufferBase
	{
	public:
		BufferBase();
		virtual ~BufferBase();

		// ���� �ʱ�ȭ(����).
		// ���� ���� �Լ� -> �������̽�.
		virtual void Initialize(ID3D11Device* device, void* data, size_t count, uint32 byteWidth) = 0;

		// ���� ���ε� (IA �ܰ迡 ���ε�).
		virtual void Bind(ID3D11DeviceContext* context) = 0;

		uint32 Count() { return count; }
		uint32 ByteWidth() { return byteWidth; }

		ID3D11Buffer* Get() { return buffer; }
		ID3D11Buffer** GetAddressOf() { return &buffer; }

	protected:
		ID3D11Buffer* buffer;	// �����͸� ������ ����.
		uint32 count;			// ������ ����.
		uint32 byteWidth;		// ������ �ϳ��� ����Ʈ ũ��.
	};
}
#endif