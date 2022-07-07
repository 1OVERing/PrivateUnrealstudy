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

		// 버퍼 초기화(생성).
		// 순수 가상 함수 -> 인터페이스.
		virtual void Initialize(ID3D11Device* device, void* data, size_t count, uint32 byteWidth) = 0;

		// 버퍼 바인딩 (IA 단계에 바인딩).
		virtual void Bind(ID3D11DeviceContext* context) = 0;

		uint32 Count() { return count; }
		uint32 ByteWidth() { return byteWidth; }

		ID3D11Buffer* Get() { return buffer; }
		ID3D11Buffer** GetAddressOf() { return &buffer; }

	protected:
		ID3D11Buffer* buffer;	// 데이터를 저장할 버퍼.
		uint32 count;			// 데이터 개수.
		uint32 byteWidth;		// 데이터 하나의 바이트 크기.
	};
}
#endif