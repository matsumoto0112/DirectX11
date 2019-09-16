struct InputBuffer
{
    int i;
};

struct OutputBuffer
{
    int i;
};

struct CSInput
{
    uint3 groupThread : SV_GroupThreadID;
    uint3 group : SV_GroupID;
    uint groupIndex : SV_GroupIndex;
    uint3 dispatch : SV_DispatchThreadID;
};

StructuredBuffer<InputBuffer> input0 : register(t0);
StructuredBuffer<InputBuffer> input1 : register(t1);
RWStructuredBuffer<OutputBuffer> out0 : register(u0);

#define SIZE_X 16
#define SIZE_Y 16
#define SIZE_Z 1

[numthreads(SIZE_X, SIZE_Y, SIZE_Z)]
void main(const CSInput input)
{
    int index = input.dispatch.x * SIZE_Y + input.dispatch.y;

    out0[index].i = input0[index].i + input1[index].i;
}