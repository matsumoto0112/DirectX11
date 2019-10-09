#include "FBXLoader.h"
#include <iostream>
#include "Framework/Define/Path.h"
#include "Framework/Define/Resource/VertexShader.h"
#include "Framework/Define/Resource/PixelShader.h"
#include "Framework/Graphics/Texture/TextureLoader.h"
#include "Framework/Graphics/Model/Animation.h"
#include "Framework/Graphics/Model/Bone.h"
#include "Framework/Graphics/Model/Motion.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/HashCombine.h"
#include "..\..\Utility\IO\FBXLoader.h"

namespace {
static const Framework::Math::Vector3 DefaultNormal(0.0f, 0.0f, 1.0f);
static const Framework::Math::Vector2 DefaultUV(0.0f, 0.0f);
static const Framework::Graphics::Color4 DefaultColor(1.0f, 1.0f, 1.0f, 1.0f);

Framework::Graphics::Color4 convertFromFbxDouble(const FbxDouble3& value, double mult) {
    Framework::Graphics::Color4 result;
    //if (mult != 1) {
    result.r = (float)(value[0] * mult);
    result.g = (float)(value[1] * mult);
    result.b = (float)(value[2] * mult);
    //}
    result.a = 1.0f;
    return result;
}

int findBone(std::set<std::pair<std::string, int>> set, const std::string& name) {
    for (auto&& s : set) {
        if (s.first == name) {
            return s.second;
        }
    }
    return -1;
}

//モデルのテクスチャが格納されているパスを取得
std::string createModelTexturePath(const std::string& modelFilePath) {
    //モデルへのパスからtextures以下にテクスチャが存在する
    return modelFilePath.substr(0, modelFilePath.rfind('/')) + "/textures/";
}

//メッシュが三角形メッシュかどうか調べる
bool isTriangle(FbxMesh* mesh) {
    int polyCount = mesh->GetPolygonCount();
    for (int i = 0; i < polyCount; i++) {
        int polySize = mesh->GetPolygonSize(i);
        if (polySize != 3) {
            return false;
        }
    }
    return true;
}

//読み込んだ頂点を正しくコントロールするための行列の作成
FbxAMatrix createPositionOffsetMatrix(FbxMesh* mesh) {
    //こうやるのが正しいはずだがうまく描画されなくなる
    //FbxVector4 T = mesh->GetNode()->GetGeometricTranslation(FbxNode::eSourcePivot);
    //FbxVector4 R = mesh->GetNode()->GetGeometricRotation(FbxNode::eSourcePivot);
    //FbxVector4 S = mesh->GetNode()->GetGeometricScaling(FbxNode::eSourcePivot);
    //FbxAMatrix TRS = FbxAMatrix(T, R, S);

    //初期姿勢をそのまま使用するとなぜかうまくいく
    FbxTime time(0);
    FbxAMatrix mat = mesh->GetNode()->EvaluateGlobalTransform(time);
    return mat;
}

//読み込んだ頂点座標からVector3に変換する
Framework::Math::Vector4 convertPositionFromSourcePosition(const FbxVector4& pos) {
    Framework::Math::Vector4 res;
    //xだけ反転しているっぽいので修正
    res.x = -(float)pos[0];
    res.y = (float)pos[1];
    res.z = (float)pos[2];
    res.w = 1.0f;
    return res;
}

//読み込んだ法線ベクトルからVector3に変換する
Framework::Math::Vector3 convertNormalFromSourceNormal(const FbxVector4& normal) {
    Framework::Math::Vector3 res;
    res.x = -(float)normal[0];
    res.y = (float)normal[1];
    res.z = (float)normal[2];
    return res.getNormal();
}

//読み込んだUV座標からVector2に変換する
Framework::Math::Vector2 convertUVFromSourceUV(const FbxVector2& uv) {
    Framework::Math::Vector2 res;
    res.x = (float)uv[0];
    res.y = 1.0f - (float)uv[1];
    return res;
}

//読み込んだ頂点カラーからColor4に変換する
Framework::Graphics::Color4 convertColorFromSourceColor(const FbxColor& color) {
    Framework::Graphics::Color4 res;
    res.r = (float)color.mRed;
    res.g = (float)color.mGreen;
    res.b = (float)color.mBlue;
    res.a = (float)color.mAlpha;
    return res;
}
}

namespace Framework {
namespace Graphics {

FBXLoader::FBXLoader()
    : mTexLoader(std::make_unique<TextureLoader>()) {
    if (!initializeSDKObjects()) {
        MY_ERROR_WINDOW(false, "初期化に失敗しました。");
    }
}

FBXLoader::~FBXLoader() {
    mFbxManager->Destroy();
}

std::unique_ptr<Model> FBXLoader::load(const std::string& filepath) {
    FbxScene* scene = importScene(Define::Path::getInstance().fbxModel() + filepath);

    const std::string texPath = createModelTexturePath(Define::Path::getInstance().fbxModel() + filepath);

    //モデルを形成するメッシュとマテリアルリストを生成する
    const int meshNum = scene->GetMemberCount<FbxMesh>();
    std::vector<std::unique_ptr<Mesh>> meshes(meshNum);
    const int matNum = scene->GetMaterialCount();
    std::vector<std::unique_ptr<Material>> materials(matNum);

    //まずはマテリアルを読み込む
    //メッシュにマテリアル番号を割り当てるため
    for (int i = 0; i < matNum; i++) {
        materials[i] = loadMaterial(texPath, scene->GetMaterial(i));
    }

    for (int i = 0; i < meshNum; i++) {
        FbxMesh* mesh = scene->GetMember<FbxMesh>(i);
        meshes[i] = (loadMesh(mesh));

        //マテリアル名を取得
        FbxLayerElementMaterial* layerElementMaterial = mesh->GetElementMaterial();
        std::string materialName = "";
        if (layerElementMaterial) {
            int index = layerElementMaterial->GetIndexArray().GetAt(0);
            materialName = mesh->GetNode()->GetMaterial(index)->GetName();
        }
        else {
            materialName = mesh->GetNode()->GetMaterial(0)->GetName();
        }
        //マテリアル名が一致するものをそのメッシュが使用するマテリアルとする
        for (int j = 0; j < matNum; j++) {
            if (materials[j]->materialName == materialName) {
                meshes[i]->matIndex = j;
                break;
            }
        }
    }

    return std::make_unique<Model>(std::move(meshes), std::move(materials));
}

//std::unique_ptr<AnimationModel> FBXLoader::loadWithAnimation(const std::string& filepath) {
//    std::vector<std::unique_ptr<Mesh>> meshes;
//    mSets.clear();
//    FbxScene* scene = importScene(filepath);
//
//    std::vector<std::unique_ptr<Material>> materials;
//    const int matNum = scene->GetSrcObjectCount<FbxSurfaceMaterial>();
//    std::string texPath = createModelTexturePath(filepath);
//    const int meshNum = scene->GetMemberCount<FbxMesh>();
//    std::vector<Bone*> bones;
//    std::unique_ptr<Animation> animation = std::make_unique<Animation>();
//
//    FbxArray<FbxString*> animNames;
//    scene->FillAnimStackNameArray(animNames);
//    FbxTakeInfo* take = scene->GetTakeInfo(animNames[0]->Buffer());
//    FbxLongLong start = take->mLocalTimeSpan.GetStart().Get();
//    FbxLongLong end = take->mLocalTimeSpan.GetStop().Get();
//    FbxLongLong fps60 = FbxTime::GetOneFrameValue(FbxTime::eFrames60);
//    const int animFrameNum = (int)((end - start) / fps60);
//    mStartFrame = (int)(start / fps60);
//
//    std::unique_ptr<Motion> motion = std::make_unique<Motion>(animFrameNum, Define::Animation::BONE_MAX);
//
//
//    for (int i = 0; i < meshNum; i++) {
//        FbxMesh* mesh = scene->GetMember<FbxMesh>(i);
//        meshes.emplace_back(loadMeshWithAnimation(mesh, &bones, animation.get(), motion.get()));
//        meshes[i]->matIndex = i;
//        FbxLayerElementMaterial* layerElement = mesh->GetElementMaterial();
//        if (layerElement != nullptr) {
//            int index = layerElement->GetIndexArray().GetAt(0);
//            materials.emplace_back(loadMaterial(texPath, mesh->GetNode()->GetMaterial(index)));
//        }
//        else {
//            materials.emplace_back(loadMaterial(texPath, mesh->GetNode()->GetMaterial(0)));
//        }
//    }
//
//    animation->addMotion(0, std::move(motion));
//    std::vector<std::unique_ptr<Bone>> pBones(bones.size());
//    const int size = bones.size();
//    for (int i = 0; i < size; i++) {
//        pBones[i] = std::unique_ptr<Bone>(bones[i]);
//    }
//
//    return std::make_unique<AnimationModel>(std::move(meshes), std::move(materials), std::move(pBones), std::move(animation));
//}

bool FBXLoader::initializeSDKObjects() {
    mFbxManager = FbxManager::Create();
    if (!mFbxManager) {
        return false;
    }
    FbxIOSettings* ios = FbxIOSettings::Create(mFbxManager, IOSROOT);
    mFbxManager->SetIOSettings(ios);
    return true;
}

FbxScene* FBXLoader::importScene(const std::string& filepath, bool triangulate) {
    FbxScene* scene = FbxScene::Create(mFbxManager, "");
    //シーンの読み込み
    FbxImporter* importer = FbxImporter::Create(mFbxManager, "");
    if (!importer->Initialize(filepath.c_str(), -1, mFbxManager->GetIOSettings())) {
        MY_ERROR_WINDOW(false, "モデルデータの読み込みに失敗しました。\n" + filepath);
        return nullptr;
    }
    std::cout << "FBXモデルインポート\n";
    importer->Import(scene);
    importer->Destroy();

    FbxGeometryConverter converter(mFbxManager);
    if (triangulate) {
        std::cout << "FBXモデルコンバート中\n";
        //三角形メッシュに変換
        converter.Triangulate(scene, true);
    }
    //メッシュごとにマテリアルを分割する
    converter.SplitMeshesPerMaterial(scene, true);
    std::cout << "FBXモデルシーン読み込み終了\n";
    return scene;
}

std::unique_ptr<Mesh> FBXLoader::loadMesh(FbxMesh* mesh) {
    std::unique_ptr<Mesh> result = std::make_unique<Mesh>();
    std::vector<WORD> indices = loadIndices(mesh);
    std::vector<MeshVertex> vertices = loadVertices(mesh);

    if (!isTriangle(mesh)) {
        std::cout << mesh->GetName() << "は三角形メッシュではありません\nモデルの表示が崩れます\n";
    }

    result->mVIBuffer = std::make_unique<VertexAndIndexBuffer>(vertices, indices,
        PrimitiveTopology::TriangleList);

    const Utility::ResourceManager& resManager = Utility::ResourceManager::getInstance();

    result->mVShader = resManager.getVertexShader()->getResource(Define::VertexShaderType::Model);
    result->mPShader = resManager.getPixelShader()->getResource(Define::PixelShaderType::Model);

    return std::move(result);
}

std::vector<WORD> FBXLoader::loadIndices(FbxMesh* mesh) {
    const int polyCount = mesh->GetPolygonCount();
    std::vector<WORD> indices(polyCount * 3);
    for (int i = 0; i < polyCount; i++) {
        indices[i * 3 + 0] = i * 3 + 2;
        indices[i * 3 + 1] = i * 3 + 1;
        indices[i * 3 + 2] = i * 3 + 0;
    }
    return indices;
}


std::vector<MeshVertex> FBXLoader::loadVertices(FbxMesh* mesh) {
    const int vertCount = mesh->GetPolygonVertexCount();
    std::vector<MeshVertex> vertices(vertCount);
    loadPositions(mesh, &vertices);
    loadNormals(mesh, &vertices);
    loadUVs(mesh, &vertices);
    loadColors(mesh, &vertices);

    return vertices;
}

void FBXLoader::loadPositions(FbxMesh* mesh, std::vector<MeshVertex>* vertices) {
    FbxVector4* source = mesh->GetControlPoints();
    const int cpCount = mesh->GetControlPointsCount();
    FbxAMatrix mat = createPositionOffsetMatrix(mesh);
    for (int i = 0; i < cpCount; i++) {
        source[i] = mat.MultT(source[i]);
    }

    //ポリゴン頂点分ループし、各頂点を格納していく
    const int size = mesh->GetPolygonVertexCount();
    int* polygonVertexIndex = mesh->GetPolygonVertices();
    for (int i = 0; i < size; i++) {
        int index = polygonVertexIndex[i];
        (*vertices)[i].pos = convertPositionFromSourcePosition(source[index]);
    }
}

void FBXLoader::loadNormals(FbxMesh* mesh, std::vector<MeshVertex>* vertices) {
    FbxArray<FbxVector4> normals;
    mesh->GetPolygonVertexNormals(normals);

    //法線が存在しなければデフォルトを使用
    if (normals.Size() == 0) {
        for (auto&& v : *vertices) {
            v.normal = DefaultNormal;
        }
        return;
    }

    const int size = vertices->size();
    FbxAMatrix mat = createPositionOffsetMatrix(mesh);
    for (int i = 0; i < normals.Size(); i++) {
        //法線は回転だけかけたい
        normals[i] = mat.MultT(normals[i]);
        std::cout << normals[i] << std::endl;
    }

    for (int i = 0; i < size; i++) {
        const FbxVector4& normal = normals[i];
        (*vertices)[i].normal = convertNormalFromSourceNormal(normal);
    }
}

void FBXLoader::loadUVs(FbxMesh* mesh, std::vector<MeshVertex>* vertices) {
    FbxStringList uvNames;
    mesh->GetUVSetNames(uvNames);

    //UVが存在しなければデフォルトの値を使用する
    if (uvNames.GetCount() == 0) {
        for (auto&& v : *vertices) {
            v.uv = DefaultUV;
        }
        return;
    }

    FbxArray<FbxVector2> uvs;
    //UVはセットの先頭のもののみ使用する
    mesh->GetPolygonVertexUVs(uvNames[0], uvs);
    const int size = vertices->size();
    for (int i = 0; i < size; i++) {
        const FbxVector2& uv = uvs[i];
        (*vertices)[i].uv = convertUVFromSourceUV(uv);
    }
}

void FBXLoader::loadColors(FbxMesh* mesh, std::vector<MeshVertex>* vertices) {
    const int colorElementNum = mesh->GetElementVertexColorCount();
    //頂点カラーが存在しなければデフォルトの色を設定
    if (colorElementNum == 0) {
        for (auto&& v : *vertices) {
            v.color = DefaultColor;
        }
        return;
    }
    FbxGeometryElementVertexColor* vertexColor = mesh->GetElementVertexColor(0);
    //読み込める形式かどうか調べる
    FbxLayerElement::EMappingMode mapMode = vertexColor->GetMappingMode();
    FbxLayerElement::EReferenceMode refMode = vertexColor->GetReferenceMode();
    if (mapMode == FbxLayerElement::eByPolygonVertex) {
        if (refMode == FbxLayerElement::eIndexToDirect) {
            FbxLayerElementArrayTemplate<FbxColor>& colors = vertexColor->GetDirectArray();
            FbxLayerElementArrayTemplate<int>& indices = vertexColor->GetIndexArray();
            for (int i = 0; i < indices.GetCount(); i++) {
                //インデックス順に入っている色情報を取得する
                const FbxColor& color = colors.GetAt(indices.GetAt(i));
                (*vertices)[i].color = convertColorFromSourceColor(color);
            }
        }
        else {
            MY_ASSERTION(false, "読み込めない形式のFBXファイルです。");
        }
    }
    else {
        MY_ASSERTION(false, "読み込めない形式のFBXファイルです。");
    }
}

//std::unique_ptr<Mesh> FBXLoader::loadMeshWithAnimation(FbxMesh* mesh, std::vector<Bone*>* bones,
//    Animation* animation, Motion* motion) {
//    std::unique_ptr<Mesh> result = std::make_unique<Mesh>();
//    int matIndex = 0;
//    std::vector<WORD> indices = loadIndices(mesh);
//    std::vector<AnimVert> vertices = loadVerticesWithBone(mesh);
//    const int vertexSize = vertices.size();
//
//    //スキンの数を取得
//    int skinCount = mesh->GetDeformerCount(FbxSkin::eSkin);
//    if (skinCount == 0) {
//    }
//
//    FbxSkin* skin = static_cast<FbxSkin*>(mesh->GetDeformer(0, FbxDeformer::eSkin));
//    int boneNum = skin->GetClusterCount();
//
//    //メッシュに紐づいているボーン分ループ
//    for (int bone = 0; bone < boneNum; bone++) {
//        //メッシュに紐づいているbone番目のボーンを取得
//        FbxCluster* cluster = skin->GetCluster(bone);
//        const char* name = cluster->GetLink()->GetName();
//
//
//        //今まで読み込んだボーンか調べる
//        int bone_no = findBone(mSets, name); //ボーン番号
//
//        //読み込んでいないボーンだったら
//        if (bone_no == -1) {
//            //新しく追加しIDを取得
//            bone_no = mSets.size();
//            mSets.emplace(name, bone_no);
//
//            //新しくボーン作成
//            Bone* pBone = new Bone(bone_no);
//
//            //初期姿勢行列
//            FbxAMatrix initMat;
//            cluster->GetTransformLinkMatrix(initMat);
//            initMat.mData[0][1] *= -1;
//            initMat.mData[0][2] *= -1;
//            initMat.mData[1][0] *= -1;
//            initMat.mData[2][0] *= -1;
//            initMat.mData[3][0] *= -1;
//            FbxAMatrix mat2;
//            cluster->GetTransformMatrix(mat2);
//            mat2.mData[0][1] *= -1;
//            mat2.mData[0][2] *= -1;
//            mat2.mData[1][0] *= -1;
//            mat2.mData[2][0] *= -1;
//            mat2.mData[3][0] *= -1;
//
//            ////オフセット行列に初期姿勢の逆行列を代入
//            FbxAMatrix offset = initMat.Inverse() * mat2;
//            FbxVector4 T = mesh->GetNode()->GetGeometricTranslation(FbxNode::eSourcePivot);
//            FbxVector4 R = mesh->GetNode()->GetGeometricRotation(FbxNode::eSourcePivot);
//            FbxVector4 S = mesh->GetNode()->GetGeometricScaling(FbxNode::eSourcePivot);
//            FbxAMatrix TRS = FbxAMatrix(T, R, S);
//
//
//            FbxDouble* offsetM = (FbxDouble*)offset;
//            Math::Matrix4x4 mat;
//            for (int i = 0; i < 16; i++) {
//                mat.m[i / 4][i % 4] = (float)offsetM[i];
//            }
//            //ボーンにオフセット行列をセット
//            pBone->setOffsetMatrix(mat);
//
//            //ボーンIDのキーフレームにおける行列読み込み
//            //loadKeyFrame(animNames[0], bone_no, cluster->GetLink(), motion);
//            loadKeyFrame("default", bone_no, cluster->GetLink(), motion);
//            //ボーンリストにボーン追加
//            bones->emplace_back(pBone);
//        }
//        else {
//        }
//        //ウェイトの数
//        const int weightCount = cluster->GetControlPointIndicesCount();
//        //ウェイト頂点インデックス配列
//        int* weightIndices = cluster->GetControlPointIndices();
//        //ウェイト
//        double* weight = cluster->GetControlPointWeights();
//        int* index = mesh->GetPolygonVertices();
//
//        for (int i = 0; i < weightCount; i++) {
//            int wgtIdx2 = weightIndices[i];
//
//            for (int vtxIdx = 0; vtxIdx < vertexSize; vtxIdx++) {
//                //頂点の中からウェイトがある頂点のインデックスを見つける
//                if (index[vtxIdx] != wgtIdx2)continue;
//                int wc = 0;
//                //未使用のウェイトインデックスを検索
//                for (wc = 0; wc < 4; wc++) {
//                    if (vertices[vtxIdx].weight[wc] <= 0) {
//                        break;
//                    }
//                }
//                if (4 <= wc) continue;
//                vertices[vtxIdx].weight[wc] = (float)weight[i];
//                vertices[vtxIdx].index[wc] = bone_no;
//            }
//        }
//    }
//
//    const int size = vertices.size();
//    for (int i = 0; i < size; i++) {
//        float n = 0.0f;
//        for (int weightCount = 0; weightCount < 4; weightCount++) {
//            if (vertices[i].weight[weightCount] <= 0.0f) {
//                break;
//            }
//            n += vertices[i].weight[weightCount];
//        }
//
//        for (int weightCount = 0; weightCount < 4; weightCount++) {
//            vertices[i].weight[weightCount] /= n;
//        }
//    }
//
//    result->mVIBuffer = std::make_unique<VertexAndIndexBuffer>(vertices, indices,
//        PrimitiveTopology::TriangleList);
//    //result->mVShader = std::make_unique<VertexShader>("AnimationVS");
//    //result->mPShader = std::make_unique<PixelShader>("AnimationPS");
//
//    return std::move(result);
//}
//
//
//
//
//std::vector<AnimVert> FBXLoader::loadVerticesWithBone(FbxMesh * mesh) {
//    const int vertCount = mesh->GetPolygonVertexCount();
//    std::vector<AnimVert> vertices(vertCount);
//    //一旦通常メッシュ頂点として読み込む
//    std::vector<MeshVertex> meshVertices(vertCount);
//    loadPositions(mesh, &meshVertices);
//    loadNormals(mesh, &meshVertices);
//    loadUVs(mesh, &meshVertices);
//    loadColors(mesh, &meshVertices);
//    //読み込んだデータをアニメーション用頂点に流しこむ
//    for (int i = 0; i < vertCount; i++) {
//        vertices[i].pos = meshVertices[i].pos;
//        vertices[i].normal = meshVertices[i].normal;
//        vertices[i].uv = meshVertices[i].uv;
//        vertices[i].color = meshVertices[i].color;
//    }
//
//    return vertices;
//}



void FBXLoader::loadKeyFrame(const std::string& name,
    int bone, FbxNode* boneNode, Motion* motion) {
    //アニメーション読み込み
    double time = (double)mStartFrame * 1.0 / 60.0;
    FbxTime T;
    int fn = motion->getKeyFrameNum();
    for (int i = 0; i < fn; i++) {
        T.SetSecondDouble(time);
        FbxAMatrix m = boneNode->EvaluateGlobalTransform(T);
        m.mData[0][1] *= -1;
        m.mData[0][2] *= -1;
        m.mData[1][0] *= -1;
        m.mData[2][0] *= -1;
        m.mData[3][0] *= -1;

        FbxDouble* matrixM = (FbxDouble*)m;
        Math::Matrix4x4 mat;
        for (int j = 0; j < 16; j++) {
            mat.m[j / 4][j % 4] = (float)matrixM[j];
        }
        motion->setKeyFrame(i, bone, mat);
        time += 1.0 / 60.0;
    }
}

std::unique_ptr<Material> FBXLoader::loadMaterial(const std::string& texPath, FbxSurfaceMaterial* material) {
    std::unique_ptr<Material> result = std::make_unique<Material>();
    if (!material) {
        return result;
    }
    result->materialName = material->GetName();

    FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
    loadMaterialFromProperty(texPath, material, PropertyType::Diffuse, *result);
    prop = material->FindProperty(FbxSurfaceMaterial::sAmbient);
    loadMaterialFromProperty(texPath, material, PropertyType::Ambient, *result);
    prop = material->FindProperty(FbxSurfaceMaterial::sSpecular);
    loadMaterialFromProperty(texPath, material, PropertyType::Specular, *result);


    return result;
}

void FBXLoader::loadMaterialFromProperty(const std::string& texPath,
    FbxSurfaceMaterial* material, PropertyType type, Material& result) {
    FbxProperty prop;
    FbxProperty factorProp;
    switch (type) {
    case Graphics::FBXLoader::PropertyType::Ambient:
        prop = material->FindProperty(FbxSurfaceMaterial::sAmbient);
        factorProp = material->FindProperty(FbxSurfaceMaterial::sAmbientFactor);
        break;
    case Graphics::FBXLoader::PropertyType::Diffuse:
        prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
        factorProp = material->FindProperty(FbxSurfaceMaterial::sDiffuseFactor);
        break;
    case Graphics::FBXLoader::PropertyType::Specular:
        prop = material->FindProperty(FbxSurfaceMaterial::sSpecular);
        factorProp = material->FindProperty(FbxSurfaceMaterial::sSpecularFactor);
        break;
    }

    if (!prop.IsValid()) {
        MY_DEBUG_LOG(Utility::StringBuilder("") << prop.GetName() << "is invalid");
        return;
    }

    std::string name = "";
    //レイヤードテクスチャを検索
    int layerdTextureCount = prop.GetSrcObjectCount<FbxLayeredTexture>();
    //存在したらレイヤードテクスチャを使用している
    if (layerdTextureCount > 0) {
        FbxLayeredTexture* layeredTexture = prop.GetSrcObject<FbxLayeredTexture>(0);
        FbxFileTexture* texture = layeredTexture->GetSrcObject<FbxFileTexture>(0);
        name = texture->GetRelativeFileName();
    }
    else {
        int fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();
        if (fileTextureCount > 0) {
            FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>();
            name = texture->GetRelativeFileName();
        }
    }
    if (name != "") {
        int pos = name.rfind('/');
        if (pos == std::string::npos) {
            pos = name.rfind('\\');
        }
        name = name.substr(pos + 1);

        if (name.rfind('.') == std::string::npos) {
            name += ".jpg";
        }

        std::shared_ptr<Texture> tex = mTexLoader->load(texPath + name);
        switch (type) {
        case Graphics::FBXLoader::PropertyType::Ambient:
            result.mAmbientMap = tex;
            break;
        case Graphics::FBXLoader::PropertyType::Diffuse:
            result.mDiffuseMap = tex;
            break;
        case Graphics::FBXLoader::PropertyType::Specular:
            result.mSpecularMap = tex;
            break;
        }
    }

    FbxDouble3 factor = prop.Get<FbxDouble3>();
    float factorValue = (float)factorProp.Get<FbxDouble>();
    Color4 color = convertFromFbxDouble(factor, factorValue);

    switch (type) {
    case Graphics::FBXLoader::PropertyType::Ambient:
        result.ambient = color;
        break;
    case Graphics::FBXLoader::PropertyType::Diffuse:
        result.diffuse = color;
        break;
    case Graphics::FBXLoader::PropertyType::Specular:
        result.specular = color;
        break;
    }
}
} //Graphics 
} //Framework 
