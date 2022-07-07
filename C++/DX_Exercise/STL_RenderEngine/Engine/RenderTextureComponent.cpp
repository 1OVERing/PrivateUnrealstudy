#include "Core.h"
#include "RenderTextureComponent.h"
#include "Util/STLException.h"
#include "Engine.h"

namespace Ronnie
{
	RTTI_DEFINITIONS(RenderTextureComponent)

	RenderTextureComponent::RenderTextureComponent()
		: renderTargetTexture(nullptr),
		renderTargetView(nullptr),
		shaderResourceView(nullptr)
	{	
	}

	RenderTextureComponent::~RenderTextureComponent()
	{
		SafeRelease(renderTargetTexture);
		SafeRelease(renderTargetView);
		SafeRelease(shaderResourceView);
	}
	
	void RenderTextureComponent::Initialize(ID3D11Device* device)
	{
		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = Engine::ScreenWidth();
		textureDesc.Height = Engine::ScreenHeight();
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		auto result = device->CreateTexture2D(&textureDesc, nullptr, &renderTargetTexture);
		ThrowIfFailed(result, "Failed to create render target texture in RenderTextureComponent.");

		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc = {};
		renderTargetViewDesc.Format = textureDesc.Format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;

		result = device->CreateRenderTargetView(renderTargetTexture, &renderTargetViewDesc, &renderTargetView);
		ThrowIfFailed(result, "Failed to create render target view in RenderTextureComponent.");

		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
		shaderResourceViewDesc.Format = textureDesc.Format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;

		result = device->CreateShaderResourceView(renderTargetTexture, &shaderResourceViewDesc, &shaderResourceView);
		ThrowIfFailed(result, "Failed to create shader resource view in RenderTextureComponent.");
	}
	
	void RenderTextureComponent::Update(ID3D11DeviceContext* context, float deltaTime)
	{
	}
	
	void RenderTextureComponent::Bind(ID3D11DeviceContext* context)
	{
		context->OMSetRenderTargets(1, &renderTargetView, Engine::GetDepthStencilView());
	}

	void RenderTextureComponent::Clear(ID3D11DeviceContext* context, float r, float g, float b, float a)
	{
		float color[4] = { r, g, b, a };
		context->ClearRenderTargetView(renderTargetView, color);
		context->ClearDepthStencilView(Engine::GetDepthStencilView(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
	
	ID3D11ShaderResourceView* RenderTextureComponent::GetShaderResourceView()
	{
		return shaderResourceView;
	}
}