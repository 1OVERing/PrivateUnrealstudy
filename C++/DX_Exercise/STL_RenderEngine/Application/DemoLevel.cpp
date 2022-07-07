#include "DemoLevel.h"
#include <Renderer/VertexDeclaration.h>
#include <Component/Actor.h>
#include <Component/StaticMeshComponent.h>

#include <Component/CameraComponent.h>
#include "PlayerController.h"
#include <Core/Engine.h>

#include "CameraController.h"
#include "Device/GameTimer.h"

#include "SquidGameActor.h"
#include "QuadActor.h"

#include "Util/Logger.h"

namespace Ronnie
{
	DemoLevel::DemoLevel()
	{
	}

	DemoLevel::~DemoLevel()
	{
	}

	void DemoLevel::Initialize(ID3D11Device* device
		, Engine* const engine)
	{
		// 머티리얼 생성.
		Material* squidMat1 = new Material(&defaultShader);
		squidMat1->AddTexture(new Texture(L"PinkSoldier_BaseColor_1001.png"));
		AddMaterial(squidMat1);

		Material* squidMat2 = new Material(&defaultShader);
		squidMat2->AddTexture(new Texture(L"PinkSoldier_BaseColor_1002.png"));
		AddMaterial(squidMat2);

		// 머티리얼 생성.
		Material* squidMatDiffuse1 = new Material(&diffuseShader);
		squidMatDiffuse1->AddTexture(new Texture(L"PinkSoldier_BaseColor_1001.png"));
		AddMaterial(squidMatDiffuse1);

		Material* squidMatDiffuse2 = new Material(&diffuseShader);
		squidMatDiffuse2->AddTexture(new Texture(L"PinkSoldier_BaseColor_1002.png"));
		AddMaterial(squidMatDiffuse2);

		// 머티리얼 생성.
		Material* squidMatSpecular1 = new Material(&specularShader);
		squidMatSpecular1->AddTexture(new Texture(L"PinkSoldier_BaseColor_1001.png"));
		AddMaterial(squidMatSpecular1);

		Material* squidMatSpecular2 = new Material(&specularShader);
		squidMatSpecular2->AddTexture(new Texture(L"PinkSoldier_BaseColor_1002.png"));
		AddMaterial(squidMatSpecular2);

		// 머티리얼 생성.
		Material* squidMatNormalmap1 = new Material(&normalMappingShader);
		squidMatNormalmap1->AddTexture(new Texture(L"PinkSoldier_BaseColor_1001.png"));
		squidMatNormalmap1->AddTexture(new Texture(L"PinkSoldier_Normal_1001.png"));
		AddMaterial(squidMatNormalmap1);

		Material* squidMatNormalmap2 = new Material(&normalMappingShader);
		squidMatNormalmap2->AddTexture(new Texture(L"PinkSoldier_BaseColor_1002.png"));
		squidMatNormalmap2->AddTexture(new Texture(L"PinkSoldier_Normal_1002.png"));
		AddMaterial(squidMatNormalmap2);

		

		// 오징어 게임 모델링 액터 생성.
		SquidGameActor* squidGameCharacter = new SquidGameActor(device);
		squidGameCharacter->SetPosition(-150.0f, 0.0f, 0.0f);
		squidGameCharacter->SetMaterial(squidMat1, squidMat2);
		AddActor(squidGameCharacter);

		// 오징어 게임 모델링 액터 생성.
		SquidGameActor* squidGameCharacter2 = new SquidGameActor(device);
		squidGameCharacter2->SetPosition(-50.0f, 0.0f, 0.0f);
		squidGameCharacter2->SetMaterial(squidMatDiffuse1, squidMatDiffuse2);
		AddActor(squidGameCharacter2);

		// 오징어 게임 모델링 액터 생성.
		SquidGameActor* squidGameCharacter3 = new SquidGameActor(device);
		squidGameCharacter3->SetPosition(50.0f, 0.0f, 0.0f);
		squidGameCharacter3->SetMaterial(squidMatSpecular1, squidMatSpecular2);
		AddActor(squidGameCharacter3);

		// 오징어 게임 모델링 액터 생성.
		SquidGameActor* squidGameCharacter4 = new SquidGameActor(device);
		squidGameCharacter4->SetPosition(150.0f, 0.0f, 0.0f);
		squidGameCharacter4->SetMaterial(squidMatNormalmap1, squidMatNormalmap2);
		AddActor(squidGameCharacter4);

		Material* quadMaterial = new Material(&multiTextureShader);
		quadMaterial->AddTexture(new Texture(TEXT("BaseTexture.jpg")));
		quadMaterial->AddTexture(new Texture(TEXT("LightMap.jpg")));
		AddMaterial(quadMaterial);

		// 쿼드 게임 모델링 액터 생성.
		QuadActor* quadActor = new QuadActor(device);
		quadActor->SetPosition(250.0f, 50.0f, 0.0f);
		quadActor->SetScale(50.0f, 50.0f, 50.0f);
		quadActor->SetMaterial(quadMaterial);
		AddActor(quadActor);

		// 카메라 추가.
		Actor* cameraActor = new Actor(device, TEXT("MainCameraActor"));
		cameraActor->SetPosition(0.0f, 30.0f, -200.0f);
		cameraActor->AddComponent(new CameraComponent(
			60.0f * MathHelper::Deg2Rad,
			static_cast<float>(engine->ScreenWidth()), 
			static_cast<float>(engine->ScreenHeight()),
			0.1f, 
			10000.0f
		));

		auto camController = new CameraController();
		camController->SetMovespeed(100.0f);
		cameraActor->AddComponent(camController);

		AddActor(cameraActor);

		// 조명.
		light.SetLightPosition(0.0f, 0.0f, -500.0f);
		light.SetDiffuseColor(1.0f, 1.0f, 1.0f);
		light.SetAmbientColor(1.0f, 1.0f, 1.0f);
		light.SetAmbientPower(0.1f);
		light.SetSpecularColor(1.0f, 1.0f, 1.0f);
		light.SetSpecularPower(32.0f);
		light.Initialize(device);

		Level::Initialize(device, engine);
	}

	void DemoLevel::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		light.Update(context);
		Level::Update(context, deltaTime);
	}

	void DemoLevel::Render(ID3D11DeviceContext* context)
	{
		light.Bind(context, 0);
		Level::Render(context);
	}
}