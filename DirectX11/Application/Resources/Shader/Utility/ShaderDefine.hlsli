static const int MAX_DIRECTIONALLIGHT = 4; //�ő啽�s������
static const int MAX_POINTLIGHT = 4; //�ő�_������
static const int MAX_CAMERA_NUM = 4; //�ő�J������

static const int MAX_BONES = 256; //�ő�{�[����

static const float EPSILON = 1e-6; //�덷

static const float4 LIGHT_COLOR = float4(255.0f / 255, 165.0f / 255, 0.0f / 255, 1.0f);
static const float3 SHADOW_COLOR = float3(0.0f, 0.0f, 0.0f);

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

//���C�g�o�b�t�@
cbuffer CB1 : register(b1)
{
    DirectionalLight dirLights[MAX_DIRECTIONALLIGHT];
    PointLight pLights[MAX_POINTLIGHT];
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

//�X�L�j���O���
cbuffer Skinning : register(b6)
{
    float4x4 bones[MAX_BONES];
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

matrix MVP()
{
    matrix res = mul(mat.world, mat.view);
    res = mul(res, mat.proj);
    return res;
}