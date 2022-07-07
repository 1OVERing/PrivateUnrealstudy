#pragma once

// ���� ������ ����.
#ifndef _INDEX_BUFFER_
#define _INDEX_BUFFER_

#include "Core.h"
#include "BufferBase.h"

namespace Ronnie
{
	class ENGINE_API IndexBuffer : public BufferBase
	{
	public:
		IndexBuffer();
		~IndexBuffer();

		// ���� ���� �ʱ�ȭ(����).
		virtual void Initialize(ID3D11Device* device, void* data, size_t count, uint32 byteWidth) override;

		// ���� ���� ���ε� (IA �ܰ迡 ���ε�).
		virtual void Bind(ID3D11DeviceContext* context) override;
		void Draw(ID3D11DeviceContext* context);
	};
}

#endif