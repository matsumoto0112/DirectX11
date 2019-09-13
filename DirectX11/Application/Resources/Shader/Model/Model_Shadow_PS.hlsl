#include "../Utility/ShaderDefine.hlsli"
Texture2D depthMapTex : register(t1);
Texture2D diffuseTex : register(t2);
SamplerState samplerWrap : register(s0);
SamplerState samplerClamp : register(s1);

struct ps_input
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
    float4 lightViewPosition : TEXCOORD1;
    float3 lightPos : TEXCOORD2;
};

float4 main(ps_input input) : SV_TARGET
{
    float4 o;

    float bias = 0.005f;
    float4 ambientLight = float4(0.15f, 0.15f, 0.15f, 1.0f);
    //float4 ambientLight = float4(1.0f, 1.0f, 1.0f, 1.0f);

    //float4 diffuseLight = float4(1.0f, 1.0f, 1.0f, 1.0f);
    float4 diffuseLight = float4(0, 0, 0, 1);
    o = ambientLight;

    float2 texCoord;
    texCoord.x = input.lightViewPosition.x / input.lightViewPosition.w / 2.0f + 0.5f;
    texCoord.y = -input.lightViewPosition.y / input.lightViewPosition.w / 2.0f + 0.5f;

    if ((saturate(texCoord.x) == texCoord.x) && (saturate(texCoord.y) == texCoord.y))
    {
        float depthValue = depthMapTex.Sample(samplerClamp, texCoord).r;
        float lightDepthValue = input.lightViewPosition.z / input.lightViewPosition.w;
        lightDepthValue = lightDepthValue - bias;
        if (lightDepthValue < depthValue)
        {
            //float lightIntensity = saturate(dot(input.normal, input.lightPos));
            //if (lightIntensity > 0)
            //{
            //    o += (diffuseLight * lightIntensity);
            //    o = saturate(o);
            //}
            o.rgb *= 0.5f;
        }
        else
        {
        }
    }
    float4 texColor = diffuseTex.Sample(samplerWrap, input.uv);
    o = o * texColor;

    return o;
}