#include "../Utility/ShaderDefine.hlsli"

struct GSInput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
    float4 col : COLOR;
};

float4x4 createBillBoard(float4x4 worldView)
{
    worldView._m20 = worldView._m30;
    worldView._m21 = worldView._m31;
    worldView._m22 = worldView._m32;
    float l = sqrt(worldView._m20 * worldView._m20 + worldView._m21 * worldView._m21 + worldView._m22 * worldView._m22);

    worldView._m20 /= l;
    worldView._m21 /= l;
    worldView._m22 /= l;

    worldView._m00 = worldView._m32;
    worldView._m01 = 0.0f;
    worldView._m02 = -worldView._m30;
    l = sqrt(worldView._m00 * worldView._m00 + worldView._m01 * worldView._m01 + worldView._m02 * worldView._m02);
    worldView._m00 /= l;
    worldView._m01 /= l;
    worldView._m02 /= l;

    worldView._m10 = worldView._m21 * worldView._m02 - worldView._m22 * worldView._m01;
    worldView._m11 = worldView._m22 * worldView._m00 - worldView._m20 * worldView._m02;
    worldView._m12 = worldView._m20 * worldView._m01 - worldView._m21 * worldView._m00;
    return worldView;
}

#define MAX_VERTEX_COUNT (6)
[maxvertexcount(MAX_VERTEX_COUNT)]
void main(point GSInput input[1], inout TriangleStream<PSInput> output)
{
    float4x4 m = mul(mat3D.world, mat3D.view);
    m = mul(createBillBoard(m), mat3D.proj);

    float4 pos[4] =
    {
        float4(-0.5f, 0.5f, 0.0f, 1.0f),
        float4(0.5f, 0.5f, 0.0f, 1.0f),
        float4(0.5f, -0.5f, 0.0f, 1.0f),
        float4(-0.5f, -0.5f, 0.0f, 1.0f),
    };

    float2 uv[4] =
    {
        float2(0.0f, 0.0f),
        float2(1.0f, 0.0f),
        float2(1.0f, 1.0f),
        float2(0.0f, 1.0f)
    };

    uint indices[MAX_VERTEX_COUNT] =
    {
        0, 1, 2, 0, 2, 3,
    };

    PSInput o = (PSInput) 0;
    o.col = input[0].color;

    uint i;
    [unroll]
    for (i = 1; i <= MAX_VERTEX_COUNT; i++)
    {
        o.pos = pos[indices[i - 1]];
        o.pos += input[0].pos;
        o.pos = mul(o.pos, m);
        o.uv = uv[indices[i - 1]];
        output.Append(o);
        if (i % 3 == 0)
            output.RestartStrip();
    }
}