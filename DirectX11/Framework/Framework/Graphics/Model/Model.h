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
* @brief ���f���̊g���q
*/
enum class ModelExtension {
    OBJ,
    FBX,
};

/**
* @struct Mesh
* @brief ���b�V���Ǘ��N���X
*/
struct Mesh {
    std::unique_ptr<VertexAndIndexBuffer> mVIBuffer;
    std::shared_ptr<VertexShader> mVShader;
    std::shared_ptr<PixelShader> mPShader;
    int matIndex;
};

/**
* @struct Material
* @brief �}�e���A���Ǘ��N���X
*/
struct Material {
    std::string materialName; //!< �}�e���A����
    Color4 ambient; //!< �A���r�G���g�J���[
    Color4 diffuse; //!< �f�B�t���[�Y�J���[
    Color4 specular; //!< �X�y�L�����[�J���[
    float shininess; //!< Shininess
    float alpha; //!< �A���t�@�l
    std::shared_ptr<Texture> mAmbientMap; //!< �A���r�G���g�}�b�v
    std::shared_ptr<Texture> mDiffuseMap; //!< �f�B�t���[�Y�}�b�v
    std::shared_ptr<Texture> mSpecularMap; //!< �X�y�L�����[�}�b�v
    std::shared_ptr<Texture> mBumpMap; //!< �o���v�}�b�v
};

/**
* @class Model
* @brief ���f���Ǘ��N���X
*/
class Model {
public:
    /**
    * @brief �R���X�g���N�^
    * @param meshes ���b�V�����X�g
    * @param materials �}�e���A�����X�g
    */
    Model(std::vector<std::unique_ptr<Mesh>> meshes,
        std::vector<std::unique_ptr<Material>> materials);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Model();
    /**
    * @brief �`�悷��
    * @details IRenderer�N���X����Ă΂��
    ����ȊO�̏󋵂ŌĂ΂��ƕ`�悪���܂������Ȃ����Ƃ�����
    */
    virtual void draw(const Utility::Transform& transform);
    /**
    * @brief ���b�V�����Ƃ̒��_�V�F�[�_�[���擾����
    */
    std::vector<std::shared_ptr<VertexShader>> getVertexShader() const;
    /**
    * @brief ���b�V�����Ƃ̃s�N�Z���V�F�[�_�[���擾����
    */
    std::vector<std::shared_ptr<PixelShader>> getPixelShader() const;
    /**
    * @brief ���_�V�F�[�_�[��ݒ肷��
    * @param vshader ���_�V�F�[�_�[
    * @param indices �ݒ肷�郁�b�V���ԍ�
    * @details indices�������Ȃ���΂��ׂẴ��b�V���ɓK�p����
    */
    void setVertexShader(std::shared_ptr<VertexShader> vshader, const std::vector<int>& indices = {});
    /**
    * @brief ���_�V�F�[�_�[��ݒ肷��
    * @param vshaders ���_�V�F�[�_�[���X�g
    */
    void setVertexShader(const std::vector<std::shared_ptr<VertexShader>>& vshaders);
    /**
    * @brief �s�N�Z���V�F�[�_�[��ݒ肷��
    * @param pshader �s�N�Z���V�F�[�_�[
    * @param indices �ݒ肷�郁�b�V���ԍ�
    * @details indices�������Ȃ���΂��ׂẴ��b�V���ɓK�p����
    */
    void setPixelShader(std::shared_ptr<PixelShader> pshader, const std::vector<int>& indices = {});
    /**
    * @brief �s�N�Z���V�F�[�_�[��ݒ肷��
    * @param vshaders �s�N�Z���V�F�[�_�[���X�g
    */
    void setPixelShader(const std::vector<std::shared_ptr<PixelShader>>& pshaders);
protected:
    std::vector<std::unique_ptr<Mesh>> mMeshes; //!< ���b�V�����X�g
    std::vector<std::unique_ptr<Material>> mMaterials; //!< �}�e���A�����X�g
};

} //Graphics 
} //Framework 
