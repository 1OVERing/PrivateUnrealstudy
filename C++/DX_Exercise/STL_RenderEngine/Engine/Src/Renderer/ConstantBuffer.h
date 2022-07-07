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

		// ���� �ʱ�ȭ(����).
		virtual void Initialize(
			ID3D11Device* device, 
			void* data, 
			size_t count, 
			uint32 byteWidth) override;

		// ������ �����͸� �����ϴ� ��쿡 ����� �Լ�.
		void Update(ID3D11DeviceContext* context, void* data);
		
		// ���̴��� �����͸� ���ε�(����)�� �� ����� �Լ�.
		void VSBind(ID3D11DeviceContext* context, uint32 index);
		void PSBind(ID3D11DeviceContext* context, uint32 index);

	private:
		virtual void Bind(ID3D11DeviceContext* context) override;
	};
}
#endif