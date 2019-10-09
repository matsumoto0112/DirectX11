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

//���f���̃e�N�X�`�����i�[����Ă���p�X���擾
std::string createModelTexturePath(const std::string& modelFilePath) {
    //���f���ւ̃p�X����textures�ȉ��Ƀe�N�X�`�������݂���
    return modelFilePath.substr(0, modelFilePath.rfind('/')) + "/textures/";
}

//���b�V�����O�p�`���b�V�����ǂ������ׂ�
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

//�ǂݍ��񂾒��_�𐳂����R���g���[�����邽�߂̍s��̍쐬
FbxAMatrix createPositionOffsetMatrix(FbxMesh* mesh) {
    //�������̂��������͂��������܂��`�悳��Ȃ��Ȃ�
    //FbxVector4 T = mesh->GetNode()->GetGeometricTranslation(FbxNode::eSourcePivot);
    //FbxVector4 R = mesh->GetNode()->GetGeometricRotation(FbxNode::eSourcePivot);
    //FbxVector4 S = mesh->GetNode()->GetGeometricScaling(FbxNode::eSourcePivot);
    //FbxAMatrix TRS = FbxAMatrix(T, R, S);

    //�����p�������̂܂܎g�p����ƂȂ������܂�����
    FbxTime time(0);
    FbxAMatrix mat = mesh->GetNode()->EvaluateGlobalTransform(time);
    return mat;
}

//�ǂݍ��񂾒��_���W����Vector3�ɕϊ�����
Framework::Math::Vector4 convertPositionFromSourcePosition(const FbxVector4& pos) {
    Framework::Math::Vector4 res;
    //x�������]���Ă�����ۂ��̂ŏC��
    res.x = -(float)pos[0];
    res.y = (float)pos[1];
    res.z = (float)pos[2];
    res.w = 1.0f;
    return res;
}

//�ǂݍ��񂾖@���x�N�g������Vector3�ɕϊ�����
Framework::Math::Vector3 convertNormalFromSourceNormal(const FbxVector4& normal) {
    Framework::Math::Vector3 res;
    res.x = -(float)normal[0];
    res.y = (float)normal[1];
    res.z = (float)normal[2];
    return res.getNormal();
}

//�ǂݍ���UV���W����Vector2�ɕϊ�����
Framework::Math::Vector2 convertUVFromSourceUV(const FbxVector2& uv) {
    Framework::Math::Vector2 res;
    res.x = (float)uv[0];
    res.y = 1.0f - (float)uv[1];
    return res;
}

//�ǂݍ��񂾒��_�J���[����Color4�ɕϊ�����
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
        MY_ERROR_WINDOW(false, "�������Ɏ��s���܂����B");
    }
}

FBXLoader::~FBXLoader() {
    mFbxManager->Destroy();
}

std::unique_ptr<Model> FBXLoader::load(const std::string& filepath) {
    FbxScene* scene = importScene(Define::Path::getInstance().fbxModel() + filepath);

    const std::string texPath = createModelTexturePath(Define::Path::getInstance().fbxModel() + filepath);

    //���f�����`�����郁�b�V���ƃ}�e���A�����X�g�𐶐�����
    const int meshNum = scene->GetMemberCount<FbxMesh>();
    std::vector<std::unique_ptr<Mesh>> meshes(meshNum);
    const int matNum = scene->GetMaterialCount();
    std::vector<std::unique_ptr<Material>> materials(matNum);

    //�܂��̓}�e���A����ǂݍ���
    //���b�V���Ƀ}�e���A���ԍ������蓖�Ă邽��
    for (int i = 0; i < matNum; i++) {
        materials[i] = loadMaterial(texPath, scene->GetMaterial(i));
    }

    for (int i = 0; i < meshNum; i++) {
        FbxMesh* mesh = scene->GetMember<FbxMesh>(i);
        meshes[i] = (loadMesh(mesh));

        //�}�e���A�������擾
        FbxLayerElementMaterial* layerElementMaterial = mesh->GetElementMaterial();
        std::string materialName = "";
        if (layerElementMaterial) {
            int index = layerElementMaterial->GetIndexArray().GetAt(0);
            materialName = mesh->GetNode()->GetMaterial(index)->GetName();
        }
        else {
            materialName = mesh->GetNode()->GetMaterial(0)->GetName();
        }
        //�}�e���A��������v������̂����̃��b�V�����g�p����}�e���A���Ƃ���
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
    //�V�[���̓ǂݍ���
    FbxImporter* importer = FbxImporter::Create(mFbxManager, "");
    if (!importer->Initialize(filepath.c_str(), -1, mFbxManager->GetIOSettings())) {
        MY_ERROR_WINDOW(false, "���f���f�[�^�̓ǂݍ��݂Ɏ��s���܂����B\n" + filepath);
        return nullptr;
    }
    std::cout << "FBX���f���C���|�[�g\n";
    importer->Import(scene);
    importer->Destroy();

    FbxGeometryConverter converter(mFbxManager);
    if (triangulate) {
        std::cout << "FBX���f���R���o�[�g��\n";
        //�O�p�`���b�V���ɕϊ�
        converter.Triangulate(scene, true);
    }
    //���b�V�����ƂɃ}�e���A���𕪊�����
    converter.SplitMeshesPerMaterial(scene, true);
    std::cout << "FBX���f���V�[���ǂݍ��ݏI��\n";
    return scene;
}

std::unique_ptr<Mesh> FBXLoader::loadMesh(FbxMesh* mesh) {
    std::unique_ptr<Mesh> result = std::make_unique<Mesh>();
    std::vector<WORD> indices = loadIndices(mesh);
    std::vector<MeshVertex> vertices = loadVertices(mesh);

    if (!isTriangle(mesh)) {
        std::cout << mesh->GetName() << "�͎O�p�`���b�V���ł͂���܂���\n���f���̕\��������܂�\n";
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

    //�|���S�����_�����[�v���A�e���_���i�[���Ă���
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

    //�@�������݂��Ȃ���΃f�t�H���g���g�p
    if (normals.Size() == 0) {
        for (auto&& v : *vertices) {
            v.normal = DefaultNormal;
        }
        return;
    }

    const int size = vertices->size();
    FbxAMatrix mat = createPositionOffsetMatrix(mesh);
    for (int i = 0; i < normals.Size(); i++) {
        //�@���͉�]������������
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

    //UV�����݂��Ȃ���΃f�t�H���g�̒l���g�p����
    if (uvNames.GetCount() == 0) {
        for (auto&& v : *vertices) {
            v.uv = DefaultUV;
        }
        return;
    }

    FbxArray<FbxVector2> uvs;
    //UV�̓Z�b�g�̐擪�̂��̂̂ݎg�p����
    mesh->GetPolygonVertexUVs(uvNames[0], uvs);
    const int size = vertices->size();
    for (int i = 0; i < size; i++) {
        const FbxVector2& uv = uvs[i];
        (*vertices)[i].uv = convertUVFromSourceUV(uv);
    }
}

void FBXLoader::loadColors(FbxMesh* mesh, std::vector<MeshVertex>* vertices) {
    const int colorElementNum = mesh->GetElementVertexColorCount();
    //���_�J���[�����݂��Ȃ���΃f�t�H���g�̐F��ݒ�
    if (colorElementNum == 0) {
        for (auto&& v : *vertices) {
            v.color = DefaultColor;
        }
        return;
    }
    FbxGeometryElementVertexColor* vertexColor = mesh->GetElementVertexColor(0);
    //�ǂݍ��߂�`�����ǂ������ׂ�
    FbxLayerElement::EMappingMode mapMode = vertexColor->GetMappingMode();
    FbxLayerElement::EReferenceMode refMode = vertexColor->GetReferenceMode();
    if (mapMode == FbxLayerElement::eByPolygonVertex) {
        if (refMode == FbxLayerElement::eIndexToDirect) {
            FbxLayerElementArrayTemplate<FbxColor>& colors = vertexColor->GetDirectArray();
            FbxLayerElementArrayTemplate<int>& indices = vertexColor->GetIndexArray();
            for (int i = 0; i < indices.GetCount(); i++) {
                //�C���f�b�N�X���ɓ����Ă���F�����擾����
                const FbxColor& color = colors.GetAt(indices.GetAt(i));
                (*vertices)[i].color = convertColorFromSourceColor(color);
            }
        }
        else {
            MY_ASSERTION(false, "�ǂݍ��߂Ȃ��`����FBX�t�@�C���ł��B");
        }
    }
    else {
        MY_ASSERTION(false, "�ǂݍ��߂Ȃ��`����FBX�t�@�C���ł��B");
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
//    //�X�L���̐����擾
//    int skinCount = mesh->GetDeformerCount(FbxSkin::eSkin);
//    if (skinCount == 0) {
//    }
//
//    FbxSkin* skin = static_cast<FbxSkin*>(mesh->GetDeformer(0, FbxDeformer::eSkin));
//    int boneNum = skin->GetClusterCount();
//
//    //���b�V���ɕR�Â��Ă���{�[�������[�v
//    for (int bone = 0; bone < boneNum; bone++) {
//        //���b�V���ɕR�Â��Ă���bone�Ԗڂ̃{�[�����擾
//        FbxCluster* cluster = skin->GetCluster(bone);
//        const char* name = cluster->GetLink()->GetName();
//
//
//        //���܂œǂݍ��񂾃{�[�������ׂ�
//        int bone_no = findBone(mSets, name); //�{�[���ԍ�
//
//        //�ǂݍ���ł��Ȃ��{�[����������
//        if (bone_no == -1) {
//            //�V�����ǉ���ID���擾
//            bone_no = mSets.size();
//            mSets.emplace(name, bone_no);
//
//            //�V�����{�[���쐬
//            Bone* pBone = new Bone(bone_no);
//
//            //�����p���s��
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
//            ////�I�t�Z�b�g�s��ɏ����p���̋t�s�����
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
//            //�{�[���ɃI�t�Z�b�g�s����Z�b�g
//            pBone->setOffsetMatrix(mat);
//
//            //�{�[��ID�̃L�[�t���[���ɂ�����s��ǂݍ���
//            //loadKeyFrame(animNames[0], bone_no, cluster->GetLink(), motion);
//            loadKeyFrame("default", bone_no, cluster->GetLink(), motion);
//            //�{�[�����X�g�Ƀ{�[���ǉ�
//            bones->emplace_back(pBone);
//        }
//        else {
//        }
//        //�E�F�C�g�̐�
//        const int weightCount = cluster->GetControlPointIndicesCount();
//        //�E�F�C�g���_�C���f�b�N�X�z��
//        int* weightIndices = cluster->GetControlPointIndices();
//        //�E�F�C�g
//        double* weight = cluster->GetControlPointWeights();
//        int* index = mesh->GetPolygonVertices();
//
//        for (int i = 0; i < weightCount; i++) {
//            int wgtIdx2 = weightIndices[i];
//
//            for (int vtxIdx = 0; vtxIdx < vertexSize; vtxIdx++) {
//                //���_�̒�����E�F�C�g�����钸�_�̃C���f�b�N�X��������
//                if (index[vtxIdx] != wgtIdx2)continue;
//                int wc = 0;
//                //���g�p�̃E�F�C�g�C���f�b�N�X������
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
//    //��U�ʏ탁�b�V�����_�Ƃ��ēǂݍ���
//    std::vector<MeshVertex> meshVertices(vertCount);
//    loadPositions(mesh, &meshVertices);
//    loadNormals(mesh, &meshVertices);
//    loadUVs(mesh, &meshVertices);
//    loadColors(mesh, &meshVertices);
//    //�ǂݍ��񂾃f�[�^���A�j���[�V�����p���_�ɗ�������
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
    //�A�j���[�V�����ǂݍ���
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
    //���C���[�h�e�N�X�`��������
    int layerdTextureCount = prop.GetSrcObjectCount<FbxLayeredTexture>();
    //���݂����烌�C���[�h�e�N�X�`�����g�p���Ă���
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
