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

OutPut Content_VS(Input _Value)
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

cbuffer UVconstant : register(b1)
{
    float XMove;
    float YMove;
    float XScale;
    float YScale;
}

cbuffer CircleMulColor : register(b2)
{
    float XPos;
    float YPos;
    float Distance;
    float MulValue;
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

float4 Content_PS(OutPut _Value) : SV_Target0
{
    float4 Color;
    
    Color = DiffuseTex.Sample(WRAPSAMPLER, float2((_Value.UV.x * XScale) + XMove, (_Value.UV.y * YScale) + YMove));
    Color.a *= MulColor.a;
    
    if (Distance > 0.0f)
    {
        
        if ((_Value.Pos.x - XPos) * (_Value.Pos.x - XPos) + (_Value.Pos.y - YPos) * (_Value.Pos.y - YPos) >= (Distance + 30) * (Distance + 30))
        {
            Color.r *= MulValue;
            Color.g *= MulValue;
            Color.b *= MulValue;
        }
        else if ((_Value.Pos.x - XPos) * (_Value.Pos.x - XPos) + (_Value.Pos.y - YPos) * (_Value.Pos.y - YPos) >= Distance * Distance)
        {
            float DistanceRatio = (Distance + 30) - sqrt((_Value.Pos.x - XPos) * (_Value.Pos.x - XPos) + (_Value.Pos.y - YPos) * (_Value.Pos.y - YPos));
           
            DistanceRatio = DistanceRatio / 30.0f;
            
            Color.r *= MulValue;
            Color.g *= MulValue;
            Color.b *= MulValue;
            
            Color.a *= 1 - DistanceRatio;
        }
        else
        {
            Color.a *= 0.0f;
        }
    }
    
    return Color;
}