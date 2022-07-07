#include "Core.h"
#include "TransformComponent.h"
#include "Util/STLException.h"

namespace Ronnie
{
	RTTI_DEFINITIONS(TransformComponent)

	TransformComponent::TransformComponent()
		: isDirty(false), transformBuffer(nullptr)
	{
		// �⺻ ��� ����.
		memset(&transformMatrix, 0, sizeof(transformMatrix));
		// ���� ��ķ� ����.
		transformMatrix = Matrix4f::Identity();
	}

	TransformComponent::~TransformComponent()
	{
		SafeRelease(transformBuffer);
	}

	void TransformComponent::Initialize(ID3D11Device* device)
	{
		// Ʈ������ ���� ����.
		D3D11_BUFFER_DESC desc = { 0 };
		desc.ByteWidth = sizeof(Matrix4f);
		desc.Usage = D3D11_USAGE_DYNAMIC;	// ������ ������ ����� ���.
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// ��� ����.
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPU ���� ����.

		// ���ۿ� ������ ������ ����.
		// ������ ��� x ȸ�� ��� x ��ġ��� -> SRT.
		transformMatrix =
			Matrix4f::Scale(transform.scale)
			* Matrix4f::Rotation(transform.rotation)
			* Matrix4f::Translation(transform.position);

		// ���ҽ�(������) ���� ����ü ����.
		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = &transformMatrix;

		// Ʈ������(���) ���� ����.
		HRESULT result = device->CreateBuffer(
			&desc, &data, &transformBuffer
		);

		// ����ó��.
		std::stringstream ss;
		ss << "Failed to transform buffer.\n"
			<< "File: " << __FILE__ << " Line: " << __LINE__ << "\n";

		//ThrowIfFailed(result, "Failed to transform buffer.");
		ThrowIfFailed(result, ss.str().c_str());
	}

	void TransformComponent::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		// �����Ͱ� �������� ���� ��쿡�� ó������ ����.
		if (isDirty == false)
		{
			return;
		}

		transformMatrix =
			Matrix4f::Scale(transform.scale)
			* Matrix4f::Rotation(transform.rotation)
			* Matrix4f::Translation(transform.position);

		D3D11_MAPPED_SUBRESOURCE mappedResource = { 0 };
		// Lock(��/���).
		context->Map(transformBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0,
			&mappedResource);
		// ������ ����.
		memcpy(mappedResource.pData, &transformMatrix,
			sizeof(transformMatrix));
		// Unlock(���/��� ����).
		context->Unmap(transformBuffer, 0);

		// ������ ������� ���� �� dirty ��Ʈ �ʱ�ȭ.
		isDirty = false;
	}

	void TransformComponent::Bind(ID3D11DeviceContext* context)
	{
		context->VSSetConstantBuffers(0, 1, &transformBuffer);
	}

	Vector3f TransformComponent::Forward() const
	{
		// �� ��ü�� �չ��� ���ϱ�.

		// ȸ�� �� �о����.
		Vector3f rot = transform.rotation;

		// �о�� ȸ�� ���� ����� ȸ�� ��� �����.
		Matrix4f rotMatrix = Matrix4f::Rotation(rot);

		// ���� ���� �չ��� ���͸� ȸ�� ��İ� ���ؼ� ȸ�� ��Ű��.
		return rotMatrix * Vector3f::Forward;
	}

	Vector3f TransformComponent::Right() const
	{
		// ȸ�� �� �о����.
		Vector3f rot = transform.rotation;

		// �о�� ȸ�� ���� ����� ȸ�� ��� �����.
		Matrix4f rotMatrix = Matrix4f::Rotation(rot);

		// ���� ���� �չ��� ���͸� ȸ�� ��İ� ���ؼ� ȸ�� ��Ű��.
		return rotMatrix * Vector3f::Right;
	}

	Vector3f TransformComponent::Up() const
	{
		// ȸ�� �� �о����.
		Vector3f rot = transform.rotation;

		// �о�� ȸ�� ���� ����� ȸ�� ��� �����.
		Matrix4f rotMatrix = Matrix4f::Rotation(rot);

		// ���� ���� �չ��� ���͸� ȸ�� ��İ� ���ؼ� ȸ�� ��Ű��.
		return rotMatrix * Vector3f::Up;
	}

	void TransformComponent::SetPosition(float x, float y, float z)
	{
		transform.position = Vector3f(x, y, z);

		// �����Ͱ� ���������� �˸��� �޼ҵ�(�Լ�).
		SetDirty();
	}

	void TransformComponent::SetPosition(const Vector3f& position)
	{
		transform.position = position;
		SetDirty();
	}

	Vector3f TransformComponent::Position() const
	{
		return transform.position;
	}

	void TransformComponent::SetRotation(float x, float y, float z)
	{
		transform.rotation = Vector3f(x, y, z);
		SetDirty();
	}

	void TransformComponent::SetRotation(const Vector3f& rotation)
	{
		transform.rotation = rotation;
		SetDirty();
	}

	Vector3f TransformComponent::Rotation() const
	{
		return transform.rotation;
	}

	void TransformComponent::SetScale(float x, float y, float z)
	{
		transform.scale = Vector3f(x, y, z);
		SetDirty();
	}

	void TransformComponent::SetScale(const Vector3f& scale)
	{
		transform.scale = scale;
		SetDirty();
	}

	Vector3f TransformComponent::Scale() const
	{
		return transform.scale;
	}

	void TransformComponent::SetDirty()
	{
		isDirty = true;
	}
}