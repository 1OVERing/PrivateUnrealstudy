#pragma once

// ���� ������ ����.
#ifndef _VERTEX_BUFFER_
#define _VERTEX_BUFFER_

#include "Core.h"
#include "BufferBase.h"

namespace Ronnie
{
	class ENGINE_API VertexBuffer : public BufferBase
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		// ���� ���� �ʱ�ȭ(����).
		virtual void Initialize(ID3D11Device* device, void* data, size_t count, uint32 byteWidth) override;

		// ���� ���� ���ε� (IA �ܰ迡 ���ε�).
		virtual void Bind(ID3D11DeviceContext* context) override;
		void Draw(ID3D11DeviceContext* context);

		uint32 ByteWidth() { return byteWidth; }

	private:
		uint32 byteWidth;		// ���� ���� �ϳ��� ����Ʈ ũ��.
	};
}

#endif