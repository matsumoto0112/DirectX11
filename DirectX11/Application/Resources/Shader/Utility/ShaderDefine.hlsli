
static const float EPSILON = 1e-6; //�덷

//���[���h�E�r���[�E�v���W�F�N�V�����s��
//2D����view��-(�J�����̍��W)�̍s�񂪓����Ă���
struct MVPMatrix
{
    matrix world; //���[���h�s��
    matrix view; //�r���[�s��
    matrix proj; //�v���W�F�N�V�����s��
};

//���s����
struct DirectionalLight
{
    float4 colDirLight; //�F
    float3 dir; //����
};

//�_����
struct PointLight
{
    float4 colPLight; //�F
    float3 posPLight; //���W
    float R; //�ő勗��
    float A; //������
};

//UV���
struct UVInfo
{
    float left;
    float top;
    float width;
    float height;
};

//�}�e���A�����
struct Material
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float shininess;
    float alpha;
};

struct LightMatrix
{
    matrix view; //���C�g�r���[�s��
    matrix proj; //���C�g�ˉe�s��
};

//���[���h�E�r���[�E�v���W�F�N�V�����s��o�b�t�@
cbuffer CB0 : register(b0)
{
    MVPMatrix mat;
}


//UV���o�b�t�@
cbuffer CB2 : register(b2)
{
    UVInfo uv;
}

//�F���o�b�t�@
cbuffer CB3 : register(b3)
{
    float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
}

//�}�e���A��
cbuffer CB5 : register(b4)
{
    Material material;
}

//�J������
cbuffer CameraNum : register(b5)
{
    int cameraNum;
}


cbuffer LightMat : register(b7)
{
    LightMatrix lightMat;
}

/**
* �@���x�N�g�������[���h�ϊ����Đ��K�����܂�
* @param nor4 4�����@���x�N�g��
* @param world ���[���h�ϊ��s��
* @return ���[���h�ϊ����Đ��K�������@���x�N�g��
*/
float3 getWorldNormal(float4 nor4, matrix world)
{
    return normalize(mul(nor4, world).xyz);
}

matrix createViewMatrix(float3 eye, float3 at, float3 up)
{
    const float3 zaxis = normalize(at - eye);
    const float3 xaxis = normalize(cross(up, zaxis));
    const float3 yaxis = cross(zaxis, xaxis);

    return float4x4(
        xaxis.x,                    yaxis.x,            zaxis.x,        0.0f,
        xaxis.y,                    yaxis.y,            zaxis.y,        0.0f,
        zaxis.z,                    yaxis.z,            zaxis.z,        0.0f,
        -dot(xaxis, eye),   -dot(yaxis, eye),   -dot(zaxis, eye),       1.0f
    );

}

matrix MVP()
{
    matrix res = mul(mat.world, mat.view);
    res = mul(res, mat.proj);
    return res;
}