struct SpotInstancer
{
    float lifeTime : IN_LIFETIME; //!< ��������
    float speed : IN_SPEED; //!< �ړ����x
    float3 position : POSITION; //!< ���W
    float3 velocity : IN_VELOCITY; //!< �ړ�����
    float4 color : COLOR; //!< �F
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