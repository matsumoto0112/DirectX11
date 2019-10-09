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
private:
    PROPERTY_POINTER(std::shared_ptr<VertexShader>, mVertexShader, VertexShader); //!< ���_�V�F�[�_�[
    PROPERTY_POINTER(std::shared_ptr<PixelShader>, mPixelShader, PixelShader); //!< �s�N�Z���V�F�[�_�[
};

} //Graphics 
} //Framework