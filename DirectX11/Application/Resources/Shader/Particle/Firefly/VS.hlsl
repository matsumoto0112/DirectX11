#ifndef INCLUDE_PARTICLE_FIREFLY_VS_HLSL
#define INCLUDE_PARTICLE_FIREFLY_VS_HLSL

struct VSInput
{
    float moveTime : IN_MOVETIME; //���b�������� 
    float nextRotateTime : IN_NEXTROTATETIME; //���̈ړ������ύX�b��
    float angle : IN_ANGLE; // ���݌����Ă������
    float3 position : POSITION; // ���ݍ��W
    float3 scale : IN_SCALE; //�X�P�[��
    float4 color : COLOR0; //�F
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