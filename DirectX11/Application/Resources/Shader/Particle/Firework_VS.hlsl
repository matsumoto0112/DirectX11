struct SpotInstancer
{
    float lifeTime : IN_LIFETIME; //!< 生存時間
    float3 position : POSITION; //!< 座標
    float3 velocity : IN_VELOCITY; //!< 移動方向
    float3 scale : IN_SCALE; //!< 大きさ
    float4 color : COLOR; //!< 色
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float3 scale : IN_SCALE;
    float4 color : COLOR0;
};

VSOutput main(const SpotInstancer input)
{
    VSOutput o = (VSOutput) 0;
    o.position = float4(input.position, 1.0f);
    o.scale = input.scale;
    o.color = input.color;
    return o;
}