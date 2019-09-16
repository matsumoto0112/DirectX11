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
RWStructuredBuffer<OutputBuffer> out0 : register(u0);

#define SIZE_X 1
#define SIZE_Y 1
#define SIZE_Z 1

[numthreads(SIZE_X, SIZE_Y, SIZE_Z)]
void main(const CSInput input)
{
    int index = input.dispatch.x;

    out0[index].i = input0[index].i * 2;
}