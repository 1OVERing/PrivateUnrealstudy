#pragma once

// 정점 데이터 버퍼.
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

		// 정점 버퍼 초기화(생성).
		virtual void Initialize(ID3D11Device* device, void* data, size_t count, uint32 byteWidth) override;

		// 정점 버퍼 바인딩 (IA 단계에 바인딩).
		virtual void Bind(ID3D11DeviceContext* context) override;
		void Draw(ID3D11DeviceContext* context);

		uint32 ByteWidth() { return byteWidth; }

	private:
		uint32 byteWidth;		// 정점 정보 하나의 바이트 크기.
	};
}

#endif