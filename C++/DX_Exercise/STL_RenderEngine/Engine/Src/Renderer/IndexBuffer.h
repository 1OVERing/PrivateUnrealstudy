#pragma once

// 정점 데이터 버퍼.
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

		// 정점 버퍼 초기화(생성).
		virtual void Initialize(ID3D11Device* device, void* data, size_t count, uint32 byteWidth) override;

		// 정점 버퍼 바인딩 (IA 단계에 바인딩).
		virtual void Bind(ID3D11DeviceContext* context) override;
		void Draw(ID3D11DeviceContext* context);
	};
}

#endif