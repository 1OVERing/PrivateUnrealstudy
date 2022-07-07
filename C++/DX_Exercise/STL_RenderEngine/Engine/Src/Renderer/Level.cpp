#include "Core.h"
#include "Level.h"
#include "Component/Actor.h"

#include "Component/CameraComponent.h"
#include "Core/Engine.h"
#include "Renderer/Material.h"

#include "Device/GameTimer.h"

#include "Util/Logger.h"

namespace Ronnie
{
	Level::Level()
		: mainCamera(nullptr)
	{
	}

	Level::~Level()
	{
		SafeDelete(mainCamera);

		for (auto actor : actors)
		{
			SafeDelete(actor);
		}

		//for (auto mesh : meshes)
		//{
		//	SafeDelete(mesh);
		//}

		for (auto material : materials)
		{
			SafeDelete(material);
		}
	}

	void Level::Initialize(ID3D11Device* device, Engine* const engine)
	{
		this->engine = engine;

		// ����ó��.
		if (mainCamera == nullptr)
		{
			throw std::exception("There's no main camera in this level.");
		}

		// ī�޶� �ʱ�ȭ.
		mainCamera->Initialize(device);

		
		// ���� �ʱ�ȭ.
		for (auto actor : actors)
		{	
			actor->Initialize(device);
		}
	}

	void Level::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		// ī�޶� ������Ʈ.
		mainCamera->Update(context, deltaTime);

		for (auto actor : actors)
		{
			actor->Update(context, deltaTime);
		}
	}

	void Level::Render(ID3D11DeviceContext* context)
	{
		CameraComponent* camera = mainCamera->GetComponent<CameraComponent>();
		if (camera != nullptr)
		{
			camera->Bind(context);
		}

		for (auto actor : actors)
		{
			actor->Render(context);
		}
	}

	void Level::AddActor(Actor* const newActor)
	{
		// ���� �߰��ϴ� ���Ͱ� CameraComponent�� ���� ������ ��쿡��
		// ���� ī�޶� ���ͷ� ����.
		CameraComponent* camera = newActor->GetComponent<CameraComponent>();
		if (camera != nullptr)
		{
			mainCamera = newActor;
			return;
		}

		// ī�޶� �ƴ� ��쿡�� �Ϲ� ���� ��Ͽ� �߰�.
		actors.emplace_back(newActor);
	}

	void Level::AddMaterial(Material* material)
	{
		materials.emplace_back(material);
	}

	void Level::AddMesh(StaticMesh* mesh)
	{
		//meshes.emplace_back(mesh);
	}
}