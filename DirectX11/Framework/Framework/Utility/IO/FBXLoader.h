#pragma once
#include <vector>
#include <string>
#include <fbxsdk.h>
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Vector3.h"
#include "Framework/Math/Vector4.h"

namespace Framework {
namespace Utility {

/**
* @class FBXLoader
* @brief FBX�ǂݍ���
*/
class FBXLoader {
public:
    /**
    * @brief �R���X�g���N�^
    * @param filepath �t�@�C���ւ̃p�X
    * @param triangulate ���b�V�����O�p�`�ɂ��邩
    */
    FBXLoader(const std::string& filepath, bool triangulate = false);
    /**
    * @brief �f�X�g���N�^
    */
    ~FBXLoader();
    /**
    * @brief �ǂݍ��ݏ���
    * @param filepath �t�@�C���ւ̃p�X
    * @param triangulate ���b�V�����O�p�`�ɂ��邩
    */
    void load(const std::string& filepath, bool triangulate = false);
    /**
    * @brief ���_���W�̎擾
    * @details �������b�V���̒��_�����ׂĎ擾����
    */
    std::vector<Math::Vector4> getPosition() const;
    /**
    * @brief ���_���W�Ƃ��̃C���f�b�N�X���擾����
    */
    void getPosition(std::vector<Math::Vector4>* position, std::vector<UINT>* index);
    /**
    * @brief �I�u�W�F�N�g��UV�������Ă��邩
    */
    bool hasUV() const;
    /**
    * @brief UV���W�̎擾
    * @details �������b�V���̂��ׂĂ�UV���W���擾����
    */
    std::vector<Math::Vector2> getUV() const;
    /**
    * @brief �@�����������Ă��邩
    */
    bool hasNormal() const;
    /**
    * @brief �@�����̎擾
    * @details �������b�V���̂��ׂĂ̖@�������擾����
    */
    std::vector<Math::Vector3> getNormal() const;
private:
    FbxManager* mManager; //!< FBX�Ǘ�
    FbxScene* mScene; //!< �ǂݍ��񂾃V�[��
};

} //Utility 
} //Framework 