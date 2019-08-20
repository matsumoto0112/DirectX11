static const int MAX_DIRECTIONALLIGHT = 4; //最大平行光源数
static const int MAX_POINTLIGHT = 4; //最大点光源数
static const int MAX_CAMERA_NUM = 4; //最大カメラ数

static const int MAX_BONES = 256; //最大ボーン数

//ワールド・ビュー・プロジェクション行列
//2D時はviewに-(カメラの座標)の行列が入ってくる
struct MVPMatrix
{
    matrix world; //ワールド行列
    matrix view; //ビュー行列
    matrix proj; //プロジェクション行列
};

//平行光源
struct DirectionalLight
{
    float4 colDirLight; //色
    float3 dir; //方向
};

//点光源
struct PointLight
{
    float4 colPLight; //色
    float3 posPLight; //座標
    float4 attPLight; //減衰パラメータ
};

//UV情報
struct UVInfo
{
    float left;
    float top;
    float width;
    float height;
};

//マテリアル情報
struct Material
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float shininess;
    float alpha;
};

//ワールド・ビュー・プロジェクション行列バッファ
cbuffer CB0 : register(b0)
{
    MVPMatrix mat;
}

//ライトバッファ
cbuffer CB1 : register(b1)
{
    DirectionalLight dirLights[MAX_DIRECTIONALLIGHT];
    PointLight pLights[MAX_POINTLIGHT];
}

//UV情報バッファ
cbuffer CB2 : register(b2)
{
    UVInfo uv;
}

//色情報バッファ
cbuffer CB3 : register(b3)
{
    float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
}

//マテリアル
cbuffer CB5 : register(b4)
{
    Material material;
}

//カメラ数
cbuffer CameraNum : register(b5)
{
    int cameraNum;
}

//スキニング情報
cbuffer Skinning : register(b6)
{
    float4x4 bones[MAX_BONES];
}

/**
* 法線ベクトルをワールド変換して正規化します
* @param nor4 4次元法線ベクトル
* @param world ワールド変換行列
* @return ワールド変換して正規化した法線ベクトル
*/
float3 getWorldNormal(float4 nor4, matrix world)
{
    return normalize(mul(nor4, world).xyz);
}