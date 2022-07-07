#pragma once

#ifndef _CONSTANT_BUFFER_
#define  _CONSTANT_BUFFER_

#include "Core.h"
#include "BufferBase.h"

namespace Ronnie
{
	class ENGINE_API ConstantBuffer : public BufferBase
	{
	public:
		ConstantBuffer();
		~ConstantBuffer();

		// 버퍼 초기화(생성).
		virtual void Initialize(
			ID3D11Device* device, 
			void* data, 
			size_t count, 
			uint32 byteWidth) override;

		// 버퍼의 데이터를 변경하는 경우에 사용할 함수.
		void Update(ID3D11DeviceContext* context, void* data);
		
		// 쉐이더에 데이터를 바인딩(연결)할 때 사용할 함수.
		void VSBind(ID3D11DeviceContext* context, uint32 index);
		void PSBind(ID3D11DeviceContext* context, uint32 index);

	private:
		virtual void Bind(ID3D11DeviceContext* context) override;
	};
}
#endif