#include "../Utility/ShaderDefine.hlsli"

struct VSInput
{
    float4 pos : POSITION;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float4 ZCalc : TEXCOORD0;
};

PSInput main(VSInput input)
{
    PSInput o = (PSInput) 0;
    o.pos = mul(input.pos, MVP());
    o.ZCalc = mul(input.pos, mat.world);
    o.ZCalc = mul(o.ZCalc, lightMat.view);
    o.ZCalc = mul(o.ZCalc, lightMat.proj);
    return o;
}