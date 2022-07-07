#include "Core.h"
#include "Light.h"

namespace Ronnie
{
	Light::Light()
		: buffer(nullptr)
	{
		buffer = new ConstantBuffer();
	}

	Light::~Light()
	{
		SafeDelete(buffer);
	}

	void Light::Initialize(ID3D11Device* device)
	{
		buffer->Initialize(device, &bufferData, 1, sizeof(LightBufferType));
	}

	void Light::Update(ID3D11DeviceContext* context)
	{
		buffer->Update(context, &bufferData);
	}

	void Light::Bind(ID3D11DeviceContext* context, uint32 index)
	{
		buffer->PSBind(context, index);
	}

	void Light::SetLightPosition(float x, float y, float z)
	{
		bufferData.lightPosition.x = x;
		bufferData.lightPosition.y = y;
		bufferData.lightPosition.z = z;
	}

	void Light::SetLightPosition(const Vector3f& position)
	{
		bufferData.lightPosition = position;
	}

	void Light::SetDiffuseColor(float r, float g, float b)
	{
		bufferData.diffuseColor.x = r;
		bufferData.diffuseColor.y = g;
		bufferData.diffuseColor.z = b;
	}

	void Light::SetAmbientColor(float r, float g, float b)
	{
		bufferData.ambientColor.x = r;
		bufferData.ambientColor.y = g;
		bufferData.ambientColor.z = b;
	}

	void Light::SetAmbientPower(float power)
	{
		bufferData.ambientPower = power;
	}

	void Light::SetSpecularColor(float r, float g, float b)
	{
		bufferData.specularColor.x = r;
		bufferData.specularColor.y = g;
		bufferData.specularColor.z = b;
	}

	void Light::SetSpecularPower(float power)
	{
		bufferData.specularPower = power;
	}
}