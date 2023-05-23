cbuffer TransformData : register(b0)
{
float4 Scale;
float4 Rotation;
float4 Quaternion;
float4 Position;

float4 LocalScale;
float4 LocalRotation;
float4 LocalQuaternion;
float4 LocalPosition;

float4 WorldScale;
float4 WorldRotation;
float4 WorldQuaternion;
float4 WorldPosition;

float4x4 ScaleMatrix;
float4x4 RotationMatrix;
float4x4 PositionMatrix;
float4x4 LocalWorldMatrix;
float4x4 WorldMatrix;
float4x4 View;
float4x4 Projection;
float4x4 ViewPort;
float4x4 WorldViewProjectionMatrix;
}

struct Input
{
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct OutPut
{
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};


cbuffer AtlasData : register(b1)
{
    float2 FramePos;
    float2 FrameScale;
}

OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);

    OutPutValue.UV.x = (_Value.UV.x * FrameScale.x) + FramePos.x;
    OutPutValue.UV.y = (_Value.UV.y * FrameScale.y) + FramePos.y;
    
    return OutPutValue;
}

cbuffer ColorOption : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
}

cbuffer UVconstant : register(b0)
{
    float XMove;
    float YMove;
    float XScale;
    float YScale;
}

cbuffer ContentColor : register(b0)
{
    float Red;
    float Green;
    float Blue;
    float Alpha;
}

Texture2D DiffuseTex : register(t0);
SamplerState WRAPSAMPLER : register(s0);

struct OutColor
{
    float4 Color0 : SV_Target0;
    float4 Color1 : SV_Target1;
    float4 Color2 : SV_Target2;
    float4 Color3 : SV_Target3;
};

float4 Texture_PS(OutPut _Value) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(WRAPSAMPLER, _Value.UV.xy);
    
    Color = DiffuseTex.Sample(WRAPSAMPLER, float2((_Value.UV.x * XScale) + XMove, (_Value.UV.y * YScale)  + YMove));
   
    Color.a *= Alpha;
    
    return Color;
}