#include "../Utility/ShaderDefine.hlsli"

struct VSInput
{
    float4 pos : POSITION;
};

struct PSInput
{
    float4 pos : SV_POSITION;
};

PSInput main(const VSInput input)
{
    PSInput o = (PSInput) 0;
    o.pos = mul(input.pos, mat.world);
    o.pos = mul(o.pos, lightMat.view);
    o.pos = mul(o.pos, lightMat.proj);
    return o;
}