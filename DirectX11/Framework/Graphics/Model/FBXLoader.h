#pragma once

#include <fbxsdk.h>
#include <tuple>
#include <set>
#include "Graphics/Model/AnimationModel.h"
#include "Graphics/Model/Model.h"
#include "Graphics/Vertex/Vertex.h"

namespace Framework {
namespace Graphics {
class TextureLoader;
class Motion;
class Bone;
class Animation;

/**
* @class FBXLoader
* @brief FBXモデル読み込み
*/
class FBXLoader {
private:
    /**
    * @enum PropertyType
    * @brief プロパティの種類定義
    */
    enum class PropertyType {
        Ambient,
        AmbientColor,
        Diffuse,
        DiffuseColor,
        Specular,
        SpeculatColor,
    };
public:
    /**
    * @brief コンストラクタ
    */
    FBXLoader();
    /**
    * @brief デストラクタ
    */
    ~FBXLoader();
    /**
    * @brief モデルの読み込み
    * @param path Resources以下からのモデルへのパス
    * @return 読み込んだモデルデータ
    */
    std::unique_ptr<Model> load(const std::string& filepath);
    /**
    * @brief モデルとアニメーションの読み込み
    * @param path Resources以下からのモデルへのパス
    * @return 読み込んだアニメーション付きモデルデータ
    */
    std::unique_ptr<AnimationModel> loadWithAnimation(const std::string& filepath);
private:
    /**
    * @brief SDKの初期化
    */
    bool initializeSDKObjects();
    /**
    * @brief モデルデータの読み込み
    * @param filepath ファイルへのパス
    */
    FbxScene* importScene(const std::string& filepath,bool triangulate = false);
    /**
    * @brief メッシュの読み込み
    * @param mesh 読み込むメッシュ
    * @return FbxMeshから読みこんだメッシュデータ
    */
    std::unique_ptr<Mesh> loadMesh(FbxMesh* mesh);
    /**
    * @brief インデックスリストを読み込む
    * @param mesh 読み込むメッシュ
    * @return メッシュから読み込んだインデックスリスト
    */
    std::vector<WORD> loadIndices(FbxMesh* mesh);
    /**
    * @brief メッシュの頂点を読み込む
    * @param mesh 読み込むメッシュ
    * @return メッシュから読み込んだメッシュの頂点リスト
    */
    std::vector<MeshVertex> loadVertices(FbxMesh* mesh);


    void loadPositions(FbxMesh* mesh, std::vector<MeshVertex>* vertices);
    void loadNormals(FbxMesh* mesh, std::vector<MeshVertex>* vertices);
    void loadUVs(FbxMesh* mesh, std::vector<MeshVertex>* vertices);
    void loadColors(FbxMesh* mesh, std::vector<MeshVertex>* vertices);

    std::vector<AnimVert> loadVerticesWithBone(FbxMesh* mesh);
    std::unique_ptr<Mesh> loadMeshWithAnimation(FbxMesh* mesh,
        std::vector<Bone*>* bones, Animation* animation, Motion* motion);

    void loadKeyFrame(const std::string& name, int bone, FbxNode* boneNode, Motion* motion);


    std::unique_ptr<Material> loadMaterial(const std::string& texPath, FbxSurfaceMaterial* material);
    void loadMaterialFromProperty(const std::string& texPath, FbxSurfaceMaterial* material, PropertyType type, Material& result);
private:
    FbxManager* mFbxManager; //!< マネージャー
    std::unique_ptr<TextureLoader> mTexLoader; //!< テクスチャ読み込み
    std::set<std::pair<std::string, int>> mSets;
    int mStartFrame;
};

} //Graphics 
} //Framework 
