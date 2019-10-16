#ifndef INCLUDE_PARTICLE_FIREFLY_VS_HLSL
#define INCLUDE_PARTICLE_FIREFLY_VS_HLSL

struct VSInput
{
    float moveTime : IN_MOVETIME; //何秒動いたら 
    float nextRotateTime : IN_NEXTROTATETIME; //次の移動方向変更秒数
    float angle : IN_ANGLE; // 現在向いている方向
    float3 position : POSITION; // 現在座標
    float3 scale : IN_SCALE; //スケール
    float4 color : COLOR0; //色
};

struct GSInput
{
    float4 pos : SV_POSITION;
    float3 scale : SCALE;
    float4 col : COLOR0;
};

GSInput main(const VSInput input)
{
    GSInput o = (GSInput) 0;
    o.pos = float4(input.position, 1.0f);
    o.scale = input.scale;
    o.col = input.color;
    return o;
}

#endif // INCLUDE_PARTICLE_FIREFLY_VS_HLSL