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
* @brief FBX���f���ǂݍ���
*/
class FBXLoader {
private:
    /**
    * @enum PropertyType
    * @brief �v���p�e�B�̎�ޒ�`
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
    * @brief �R���X�g���N�^
    */
    FBXLoader();
    /**
    * @brief �f�X�g���N�^
    */
    ~FBXLoader();
    /**
    * @brief ���f���̓ǂݍ���
    * @param path Resources�ȉ�����̃��f���ւ̃p�X
    * @return �ǂݍ��񂾃��f���f�[�^
    */
    std::unique_ptr<Model> load(const std::string& filepath);
    /**
    * @brief ���f���ƃA�j���[�V�����̓ǂݍ���
    * @param path Resources�ȉ�����̃��f���ւ̃p�X
    * @return �ǂݍ��񂾃A�j���[�V�����t�����f���f�[�^
    */
    std::unique_ptr<AnimationModel> loadWithAnimation(const std::string& filepath);
private:
    /**
    * @brief SDK�̏�����
    */
    bool initializeSDKObjects();
    /**
    * @brief ���f���f�[�^�̓ǂݍ���
    * @param filepath �t�@�C���ւ̃p�X
    */
    FbxScene* importScene(const std::string& filepath,bool triangulate = false);
    /**
    * @brief ���b�V���̓ǂݍ���
    * @param mesh �ǂݍ��ރ��b�V��
    * @return FbxMesh����ǂ݂��񂾃��b�V���f�[�^
    */
    std::unique_ptr<Mesh> loadMesh(FbxMesh* mesh);
    /**
    * @brief �C���f�b�N�X���X�g��ǂݍ���
    * @param mesh �ǂݍ��ރ��b�V��
    * @return ���b�V������ǂݍ��񂾃C���f�b�N�X���X�g
    */
    std::vector<WORD> loadIndices(FbxMesh* mesh);
    /**
    * @brief ���b�V���̒��_��ǂݍ���
    * @param mesh �ǂݍ��ރ��b�V��
    * @return ���b�V������ǂݍ��񂾃��b�V���̒��_���X�g
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
    FbxManager* mFbxManager; //!< �}�l�[�W���[
    std::unique_ptr<TextureLoader> mTexLoader; //!< �e�N�X�`���ǂݍ���
    std::set<std::pair<std::string, int>> mSets;
    int mStartFrame;
};

} //Graphics 
} //Framework 
