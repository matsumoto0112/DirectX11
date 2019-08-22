#include "ShaderDefine.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

struct PS_IN
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

struct PS_OUT
{
    float4 target0 : SV_TARGET0;
    float4 target1 : SV_TARGET1;
};

PS_OUT main(const PS_IN IN)
{
    PS_OUT output = (PS_OUT) 0;
    //ˆê‚Â–Ú‚Í•’Ê‚Éo—Í
    float4 o = tex.Sample(samLinear, IN.Tex);
    o *= color;
    output.target0 = o;
    //“ñ‚Â–Ú‚Í‹P“x‚ÌŒvZ
    float bright = smoothstep(1.0, 2.0, length(o));
    output.target1 = bright;
    //output.target1 = o;
    return output;
}