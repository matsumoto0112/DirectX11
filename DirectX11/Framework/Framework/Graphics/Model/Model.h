#pragma once

#include <memory>
#include "Framework/Graphics/Vertex/Vertex.h"
#include "Framework/Graphics/Buffer/VertexAndIndexBuffer.h"
#include "Framework/Graphics/Shader/VertexShader.h"
#include "Framework/Graphics/Shader/PixelShader.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "Framework/Graphics/Texture/Texture.h"
#include "Framework/Graphics/ConstantBuffer/MaterialCBufferStruct.h"
#include "Framework/Utility/Transform.h"

namespace Framework {
namespace Graphics {

/**
* @brief モデルの拡張子
*/
enum class ModelExtension {
    OBJ,
    FBX,
};

/**
* @struct Mesh
* @brief メッシュ管理クラス
*/
struct Mesh {
    std::unique_ptr<VertexAndIndexBuffer> mVIBuffer;
    std::shared_ptr<VertexShader> mVShader;
    std::shared_ptr<PixelShader> mPShader;
    int matIndex;
};

/**
* @struct Material
* @brief マテリアル管理クラス
*/
struct Material {
    std::string materialName; //!< マテリアル名
    Color4 ambient; //!< アンビエントカラー
    Color4 diffuse; //!< ディフューズカラー
    Color4 specular; //!< スペキュラーカラー
    float shininess; //!< Shininess
    float alpha; //!< アルファ値
    std::shared_ptr<Texture> mAmbientMap; //!< アンビエントマップ
    std::shared_ptr<Texture> mDiffuseMap; //!< ディフューズマップ
    std::shared_ptr<Texture> mSpecularMap; //!< スペキュラーマップ
    std::shared_ptr<Texture> mBumpMap; //!< バンプマップ
};

/**
* @class Model
* @brief モデル管理クラス
*/
class Model {
public:
    /**
    * @brief コンストラクタ
    * @param meshes メッシュリスト
    * @param materials マテリアルリスト
    */
    Model(std::vector<std::unique_ptr<Mesh>> meshes,
        std::vector<std::unique_ptr<Material>> materials);
    /**
    * @brief デストラクタ
    */
    virtual ~Model();
    /**
    * @brief 描画する
    * @details IRendererクラスから呼ばれる
    それ以外の状況で呼ばれると描画がうまくいかないことがある
    */
    virtual void draw(const Utility::Transform& transform);
    /**
    * @brief メッシュごとの頂点シェーダーを取得する
    */
    std::vector<std::shared_ptr<VertexShader>> getVertexShader() const;
    /**
    * @brief メッシュごとのピクセルシェーダーを取得する
    */
    std::vector<std::shared_ptr<PixelShader>> getPixelShader() const;
    /**
    * @brief 頂点シェーダーを設定する
    * @param vshader 頂点シェーダー
    * @param indices 設定するメッシュ番号
    * @details indicesが何もなければすべてのメッシュに適用する
    */
    void setVertexShader(std::shared_ptr<VertexShader> vshader, const std::vector<int>& indices = {});
    /**
    * @brief 頂点シェーダーを設定する
    * @param vshaders 頂点シェーダーリスト
    */
    void setVertexShader(const std::vector<std::shared_ptr<VertexShader>>& vshaders);
    /**
    * @brief ピクセルシェーダーを設定する
    * @param pshader ピクセルシェーダー
    * @param indices 設定するメッシュ番号
    * @details indicesが何もなければすべてのメッシュに適用する
    */
    void setPixelShader(std::shared_ptr<PixelShader> pshader, const std::vector<int>& indices = {});
    /**
    * @brief ピクセルシェーダーを設定する
    * @param vshaders ピクセルシェーダーリスト
    */
    void setPixelShader(const std::vector<std::shared_ptr<PixelShader>>& pshaders);
protected:
    std::vector<std::unique_ptr<Mesh>> mMeshes; //!< メッシュリスト
    std::vector<std::unique_ptr<Material>> mMaterials; //!< マテリアルリスト
};

} //Graphics 
} //Framework 
