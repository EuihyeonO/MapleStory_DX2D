#include "PrecompileHeader.h"
#include "ContentUIRenderer.h"


ContentUIRenderer::ContentUIRenderer()
{
}

ContentUIRenderer::~ContentUIRenderer()
{
}

void ContentUIRenderer::Start()
{
	PushCameraRender(100);

	SetMesh("Rect");
	SetPipeLine("ContentShader");

	AtlasData.x = 0.0f;
	AtlasData.y = 0.0f;
	AtlasData.z = 1.0f;
	AtlasData.w = 1.0f;

	ColorOptionValue.MulColor = float4::One;
	ColorOptionValue.PlusColor = float4::Null;

	GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);
	GetShaderResHelper().SetConstantBufferLink("ColorOption", ColorOptionValue);
	GetShaderResHelper().SetConstantBufferLink("UVconstant", UVconstant);
	GetShaderResHelper().SetConstantBufferLink("CircleMulColor", CircleMulColor);
}