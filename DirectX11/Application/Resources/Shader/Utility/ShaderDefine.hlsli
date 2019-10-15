#ifndef INCLUDE_UTILITY_SHADERDEFINE_HLSLI
#define INCLUDE_UTILITY_SHADERDEFINE_HLSLI

static const float EPSILON = 1e-6; //�덷

//���[���h�E�r���[�E�v���W�F�N�V�����s��
struct MVPMatrix3D
{
    float4x4 world; //���[���h�s��
    float4x4 view; //�r���[�s��
    float4x4 proj; //�v���W�F�N�V�����s��
};

//���[���h�E�r���[�E�v���W�F�N�V�����s��
//view��-(�J�����̍��W)�̍s�񂪓����Ă���
struct MVPMatrix2D
{
    float4x4 world; //���[���h�s��
    float4x4 view; //�r���[�s��
    float4x4 proj; //�v���W�F�N�V�����s��
};

//UV���
struct UVInfo
{
    float left;
    float top;
    float width;
    float height;
};

struct LightMatrix
{
    float4x4 view; //���C�g�r���[�s��
    float4x4 proj; //���C�g�ˉe�s��
};

//3D�p���[���h�E�r���[�E�v���W�F�N�V�����s��o�b�t�@
cbuffer CB0 : register(b0)
{
    MVPMatrix3D mat3D;
}

//2D�p���[���h�E�r���[�E�v���W�F�N�V�����s��o�b�t�@
cbuffer CB1 : register(b1)
{
    MVPMatrix2D mat2D;
}

//UV���o�b�t�@
cbuffer CB2 : register(b2)
{
    UVInfo uv;
}

//�F���o�b�t�@
cbuffer CB3 : register(b3)
{
    float4 color;
}


cbuffer LightMat : register(b7)
{
    LightMatrix lightMat;
}

matrix createViewMatrix(float3 eye, float3 at, float3 up)
{
    const float3 zaxis = normalize(at - eye);
    const float3 xaxis = normalize(cross(up, zaxis));
    const float3 yaxis = cross(zaxis, xaxis);

    return float4x4(
        xaxis.x, yaxis.x, zaxis.x, 0.0f,
        xaxis.y, yaxis.y, zaxis.y, 0.0f,
        zaxis.z, yaxis.z, zaxis.z, 0.0f,
        -dot(xaxis, eye), -dot(yaxis, eye), -dot(zaxis, eye), 1.0f
    );

}

//3D���[���h�E�r���[�E�v���W�F�N�V�����s��
float4x4 WORLD_VIEW_PROJECTION_3D()
{
    float4x4 m = mul(mat3D.world, mat3D.view);
    m = mul(m, mat3D.proj);
    return m;
}

//2D���[���h�E�r���[�E�v���W�F�N�V�����s��
float4x4 WORLD_VIEW_PROJECTION_2D()
{
    float4x4 m = mul(mat2D.world, mat2D.view);
    m = mul(m, mat2D.proj);
    return m;
}
#endif // INCLUDE_UTILITY_SHADERDEFINE_HLSLI
