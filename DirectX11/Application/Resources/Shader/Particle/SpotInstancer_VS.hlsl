struct SpotInstancer
{
    float lifeTime : IN_LIFETIME; //!< 生存時間
    float speed : IN_SPEED; //!< 移動速度
    float3 position : POSITION; //!< 座標
    float3 velocity : IN_VELOCITY; //!< 移動方向
    float4 color : COLOR; //!< 色
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
};

VSOutput main(const SpotInstancer input)
{
    VSOutput o = (VSOutput) 0;
    o.position = float4(input.position, 1.0f);
    o.color = input.color;
    return o;
}