#include "FBXLoader.h"
#include "Framework/Utility/Debug.h"

namespace {
static const Framework::Math::Vector2 DEFAULT_UV = Framework::Math::Vector2::ZERO;
static const Framework::Math::Vector3 DEFAULT_NORMAL = Framework::Math::Vector3::FORWORD;

Framework::Math::Vector4 toPositionVector4(const FbxVector4& pos) {
    Framework::Math::Vector4 result;
    result.x = static_cast<float>(pos[0]);
    result.y = static_cast<float>(pos[1]);
    result.z = static_cast<float>(pos[2]);
    result.w = 1.0f;
    return result;
}

Framework::Math::Vector2 toUVVector2(const FbxVector2& uv) {
    Framework::Math::Vector2 res;
    res.x = (float)uv[0];
    res.y = 1.0f - (float)uv[1];
    return res;
}

Framework::Math::Vector3 toNormalVector3(const FbxVector4& normal) {
    Framework::Math::Vector3 result;
    result.x = static_cast<float>(normal[0]);
    result.y = static_cast<float>(normal[1]);
    result.z = static_cast<float>(normal[2]);
    return result;
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

std::vector<Framework::Math::Vector4> positions(FbxMesh* mesh) {
    FbxVector4* source = mesh->GetControlPoints();
    const int cpCount = mesh->GetControlPointsCount();

    //初期姿勢行列を用いて頂点を正しい座標に変換する
    FbxAMatrix mat = createPositionOffsetMatrix(mesh);
    for (int i = 0; i < cpCount; i++) {
        source[i] = mat.MultT(source[i]);
    }

    //ポリゴン頂点分ループし、各頂点を格納していく
    const int size = mesh->GetPolygonVertexCount();
    int* polygonVertexIndex = mesh->GetPolygonVertices();
    std::vector<Framework::Math::Vector4> result(size);
    for (int i = 0; i < size; i++) {
        int index = polygonVertexIndex[i];
        result[i] = toPositionVector4(source[index]);
    }
    return result;
}

std::vector<Framework::Math::Vector2> uvs(FbxMesh* mesh) {
    FbxStringList uvNames;
    mesh->GetUVSetNames(uvNames);
    const int size = mesh->GetPolygonVertexCount();
    std::vector<Framework::Math::Vector2> result(size);

    //UVが存在しなければデフォルトの値を使用する
    if (uvNames.GetCount() == 0) {
        for (int i = 0; i < size; i++) {
            result[i] = DEFAULT_UV;
        }
    }
    else {
        FbxArray<FbxVector2> uvs;
        //UVはセットの先頭のもののみ使用する
        mesh->GetPolygonVertexUVs(uvNames[0], uvs);
        for (int i = 0; i < size; i++) {
            const FbxVector2& uv = uvs[i];
            result[i] = toUVVector2(uv);
        }
    }
    return result;
}

std::vector<Framework::Math::Vector3> normals(FbxMesh* mesh) {
    FbxArray<FbxVector4> normals;
    mesh->GetPolygonVertexNormals(normals);
    const int size = mesh->GetPolygonVertexCount();
    std::vector<Framework::Math::Vector3> result(size);
    //法線が存在しなければデフォルトを使用
    if (normals.Size() == 0) {
        for (int i = 0; i < size; i++) {
            result[i] = DEFAULT_NORMAL;
        }
        return result;
    }

    //FbxAMatrix mat = createPositionOffsetMatrix(mesh);
    //for (int i = 0; i < normals.Size(); i++) {
    //    normals[i] = mat.MultT(normals[i]);
    //}

    for (int i = 0; i < size; i++) {
        const FbxVector4& normal = normals[i];
        result[i] = toNormalVector3(normal);
    }
    return result;
}
}

namespace Framework {
namespace Utility {

FBXLoader::FBXLoader(const std::string& filepath, bool triangulate) {
    mManager = FbxManager::Create();
    MY_ERROR_WINDOW(mManager, "FBX初期化に失敗しました");
    FbxIOSettings* ios = FbxIOSettings::Create(mManager, IOSROOT);
    mManager->SetIOSettings(ios);

    load(filepath, triangulate);
}

FBXLoader::~FBXLoader() {
    mManager->Destroy();
}

void FBXLoader::load(const std::string& filepath, bool triangulate) {
    if (mScene)mScene->Destroy();
    mScene = FbxScene::Create(mManager, "");
    //シーンの読み込み
    FbxImporter* importer = FbxImporter::Create(mManager, "");
    if (!importer->Initialize(filepath.c_str(), -1, mManager->GetIOSettings())) {
        MY_ERROR_WINDOW(false, "モデルデータの読み込みに失敗しました。\n" + filepath);
        return;
    }

    importer->Import(mScene);
    importer->Destroy();

    FbxGeometryConverter converter(mManager);
    if (triangulate) {
        converter.Triangulate(mScene, true);
    }
    //メッシュごとにマテリアルを分割する
    converter.SplitMeshesPerMaterial(mScene, true);
}

std::vector<Math::Vector4> FBXLoader::getPosition() const {
    const int meshNum = mScene->GetMemberCount<FbxMesh>();
    std::vector<Math::Vector4> result;
    for (int i = 0; i < meshNum; i++) {
        std::vector<Math::Vector4> pos = positions(mScene->GetMember<FbxMesh>(i));
        result.insert(result.end(), pos.begin(), pos.end());
    }

    return result;
}

void FBXLoader::getPosition(std::vector<Math::Vector4>* position, std::vector<UINT>* index) {
    *position = getPosition();
    index->clear();
    const size_t size = position->size();
    index->resize(size);
    for (int i = 0; i < size / 3; i++) {
        (*index)[i * 3 + 0] = i * 3 + 2;
        (*index)[i * 3 + 1] = i * 3 + 1;
        (*index)[i * 3 + 2] = i * 3 + 0;
    } 
}

bool FBXLoader::hasUV() const {
    const int meshNum = mScene->GetMemberCount<FbxMesh>();
    for (int i = 0; i < meshNum; i++) {
        FbxStringList uvNames;
        mScene->GetMember<FbxMesh>(i)->GetUVSetNames(uvNames);
        if (uvNames.GetCount() > 0)return true;
    }
    return false;
}

std::vector<Math::Vector2> FBXLoader::getUV() const {
    const int meshNum = mScene->GetMemberCount<FbxMesh>();
    std::vector<Math::Vector2> result;

    for (int i = 0; i < meshNum; i++) {
        std::vector<Math::Vector2> uv = uvs(mScene->GetMember<FbxMesh>(i));
        result.insert(result.end(), uv.begin(), uv.end());
    }

    return result;

}

bool FBXLoader::hasNormal() const {
    const int meshNum = mScene->GetMemberCount<FbxMesh>();
    for (int i = 0; i < meshNum; i++) {
        FbxArray<FbxVector4> normals;
        mScene->GetMember<FbxMesh>(i)->GetPolygonVertexNormals(normals);
        if (normals.Size() > 0)return true;
    }
    return false;
}

std::vector<Math::Vector3> FBXLoader::getNormal() const {
    const int meshNum = mScene->GetMemberCount<FbxMesh>();
    std::vector<Math::Vector3> result;

    for (int i = 0; i < meshNum; i++) {
        std::vector<Math::Vector3> normal = normals(mScene->GetMember<FbxMesh>(i));
        result.insert(result.end(), normal.begin(), normal.end());
    }
    return result;
}

} //Utility 
} //Framework 
