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

		// 예외처리.
		if (mainCamera == nullptr)
		{
			throw std::exception("There's no main camera in this level.");
		}

		// 카메라 초기화.
		mainCamera->Initialize(device);

		
		// 액터 초기화.
		for (auto actor : actors)
		{	
			actor->Initialize(device);
		}
	}

	void Level::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		// 카메라 업데이트.
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
		// 새로 추가하는 액터가 CameraComponent를 가진 액터인 경우에는
		// 메인 카메라 액터로 설정.
		CameraComponent* camera = newActor->GetComponent<CameraComponent>();
		if (camera != nullptr)
		{
			mainCamera = newActor;
			return;
		}

		// 카메라가 아닌 경우에는 일반 액터 목록에 추가.
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