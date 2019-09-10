#pragma once

#include <memory>
#include "Framework/Graphics/Shader/PixelShader.h"
#include "Framework/Graphics/Shader/VertexShader.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class Effect
* @brief �G�t�F�N�g�N���X
*/
class Effect {
public:
    /**
    * @brief �R���X�g���N�^
    * @param vertexShader ���_�V�F�[�_�[
    * @param pixelShader �s�N�Z���V�F�[�_�[
    */
    Effect(std::shared_ptr<VertexShader> vertexShader,
        std::shared_ptr<PixelShader> pixelShader);
    /**
    * @brief �f�X�g���N�^
    */
    ~Effect();
    /**
    * @brief �V�F�[�_�[���R���e�L�X�g�ɃZ�b�g����
    */
    void set();
public:
    /**
    * @brief ���_�V�F�[�_�[���擾����
    */
    std::shared_ptr<VertexShader> getVertexShader() const { return mVertexShader; }
    /**
    * @brief ���_�V�F�[�_�[��ݒ肷��
    */
    void setVertexShader(std::shared_ptr<VertexShader> vshader) { mVertexShader = vshader; }
    /**
    * @brief �s�N�Z���V�F�[�_�[���擾����
    */
    std::shared_ptr<PixelShader> getPixelShader() const { return mPixelShader; }
    /**
    * @brief �s�N�Z���V�F�[�_�[��ݒ肷��
    */
    void setPixelShader(std::shared_ptr<PixelShader> pshader) { mPixelShader = pshader; }
private:
    std::shared_ptr<VertexShader> mVertexShader; //!< ���_�V�F�[�_�[
    std::shared_ptr<PixelShader> mPixelShader; //!< �s�N�Z���V�F�[�_�[
};

} //Graphics 
} //Framework