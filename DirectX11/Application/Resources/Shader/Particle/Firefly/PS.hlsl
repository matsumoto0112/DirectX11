struct PSInput
{
    float4 pos : SV_POSITION;
    float4 col : COLOR;
};

struct PSOutput
{
    float4 color0 : SV_TARGET0;
    float4 color1 : SV_TARGET1;
};

PSOutput main(const PSInput input)
{
    PSOutput o = (PSOutput) 0;
    o.color0 = input.col;

    float bright = smoothstep(0, 1, length(input.col.rgb));
    o.color1 = float4(bright, bright, bright, 1.0);
    return o;
}