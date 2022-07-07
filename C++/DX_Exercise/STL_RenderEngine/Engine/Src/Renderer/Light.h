#pragma once

#ifndef _LIGHT_
#define _LIGHT_

#include "Core.h"
#include "ConstantBuffer.h"
#include "Math/Vector3f.h"

namespace Ronnie
{
	class ENGINE_API Light
	{
	private:
		struct LightBufferType
		{
			Vector3f lightPosition;
			float positionPadding;
			Vector3f diffuseColor;
			float diffusePadding;
			Vector3f ambientColor;
			float ambientPower;
			Vector3f specularColor;
			float specularPower;
		};

	public:
		Light();
		~Light();

		void Initialize(ID3D11Device* device);
		void Update(ID3D11DeviceContext* context);
		void Bind(ID3D11DeviceContext* context, uint32 index);

		void SetLightPosition(float x, float y, float z);
		void SetLightPosition(const Vector3f& position);
		void SetDiffuseColor(float r, float g, float b);
		void SetAmbientColor(float r, float g, float b);
		void SetAmbientPower(float power);
		void SetSpecularColor(float r, float g, float b);
		void SetSpecularPower(float power);

		Vector3f Position() { return bufferData.lightPosition; }
		Vector3f DiffuseColor() { return bufferData.diffuseColor; }
		Vector3f AmbientColor() { return bufferData.ambientColor; }
		Vector3f SpecularColor() { return bufferData.specularColor; }
		float SpecularPower() { return bufferData.specularPower; }

	private:
		LightBufferType bufferData;
		ConstantBuffer* buffer;
	};
}

#endif