#include "Core.h"
#include "TransformComponent.h"
#include "Util/STLException.h"

namespace Ronnie
{
	RTTI_DEFINITIONS(TransformComponent)

	TransformComponent::TransformComponent()
		: isDirty(false), transformBuffer(nullptr)
	{
		// 기본 행렬 설정.
		memset(&transformMatrix, 0, sizeof(transformMatrix));
		// 단위 행렬로 설정.
		transformMatrix = Matrix4f::Identity();
	}

	TransformComponent::~TransformComponent()
	{
		SafeRelease(transformBuffer);
	}

	void TransformComponent::Initialize(ID3D11Device* device)
	{
		// 트랜스폼 버퍼 생성.
		D3D11_BUFFER_DESC desc = { 0 };
		desc.ByteWidth = sizeof(Matrix4f);
		desc.Usage = D3D11_USAGE_DYNAMIC;	// 데이터 변경이 빈번한 경우.
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// 상수 버퍼.
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPU 쓰기 설정.

		// 버퍼에 저장할 데이터 생성.
		// 스케일 행렬 x 회전 행렬 x 위치행렬 -> SRT.
		transformMatrix =
			Matrix4f::Scale(transform.scale)
			* Matrix4f::Rotation(transform.rotation)
			* Matrix4f::Translation(transform.position);

		// 리소스(데이터) 담을 구조체 생성.
		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = &transformMatrix;

		// 트랜스폼(상수) 버퍼 생성.
		HRESULT result = device->CreateBuffer(
			&desc, &data, &transformBuffer
		);

		// 예외처리.
		std::stringstream ss;
		ss << "Failed to transform buffer.\n"
			<< "File: " << __FILE__ << " Line: " << __LINE__ << "\n";

		//ThrowIfFailed(result, "Failed to transform buffer.");
		ThrowIfFailed(result, ss.str().c_str());
	}

	void TransformComponent::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		// 데이터가 수정돼지 않은 경우에는 처리하지 않음.
		if (isDirty == false)
		{
			return;
		}

		transformMatrix =
			Matrix4f::Scale(transform.scale)
			* Matrix4f::Rotation(transform.rotation)
			* Matrix4f::Translation(transform.position);

		D3D11_MAPPED_SUBRESOURCE mappedResource = { 0 };
		// Lock(락/잠금).
		context->Map(transformBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0,
			&mappedResource);
		// 데이터 복사.
		memcpy(mappedResource.pData, &transformMatrix,
			sizeof(transformMatrix));
		// Unlock(언락/잠금 해제).
		context->Unmap(transformBuffer, 0);

		// 데이터 변경사항 적용 후 dirty 비트 초기화.
		isDirty = false;
	}

	void TransformComponent::Bind(ID3D11DeviceContext* context)
	{
		context->VSSetConstantBuffers(0, 1, &transformBuffer);
	}

	Vector3f TransformComponent::Forward() const
	{
		// 이 물체의 앞방향 구하기.

		// 회전 값 읽어오기.
		Vector3f rot = transform.rotation;

		// 읽어온 회전 값을 사용해 회전 행렬 만들기.
		Matrix4f rotMatrix = Matrix4f::Rotation(rot);

		// 월드 기준 앞방향 벡터를 회전 행렬과 곱해서 회전 시키기.
		return rotMatrix * Vector3f::Forward;
	}

	Vector3f TransformComponent::Right() const
	{
		// 회전 값 읽어오기.
		Vector3f rot = transform.rotation;

		// 읽어온 회전 값을 사용해 회전 행렬 만들기.
		Matrix4f rotMatrix = Matrix4f::Rotation(rot);

		// 월드 기준 앞방향 벡터를 회전 행렬과 곱해서 회전 시키기.
		return rotMatrix * Vector3f::Right;
	}

	Vector3f TransformComponent::Up() const
	{
		// 회전 값 읽어오기.
		Vector3f rot = transform.rotation;

		// 읽어온 회전 값을 사용해 회전 행렬 만들기.
		Matrix4f rotMatrix = Matrix4f::Rotation(rot);

		// 월드 기준 앞방향 벡터를 회전 행렬과 곱해서 회전 시키기.
		return rotMatrix * Vector3f::Up;
	}

	void TransformComponent::SetPosition(float x, float y, float z)
	{
		transform.position = Vector3f(x, y, z);

		// 데이터가 수정됐음을 알리는 메소드(함수).
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