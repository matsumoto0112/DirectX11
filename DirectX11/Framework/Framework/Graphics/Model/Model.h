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
* @class Model
* @brief ���f���Ǘ��N���X
*/
class Model {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Model(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer,
        std::shared_ptr<VertexShader> vertexShader, std::shared_ptr<PixelShader> pixelShader);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Model();
    /**
    * @brief �`�悷��
    */
    virtual void draw(const Utility::Transform& transform);
    /**
    * @brief ���_�V�F�[�_�[���擾����
    */
    std::shared_ptr<VertexShader> getVertexShader() const { return mVertexShader; }
    /**
    * @brief �s�N�Z���V�F�[�_�[���擾����
    */
    std::shared_ptr<PixelShader> getPixelShader() const { return mPixelShader; }
    /**
    * @brief ���_�V�F�[�_�[��ݒ肷��
    * @param vertexShader ���_�V�F�[�_�[
    */
    void setVertexShader(std::shared_ptr<VertexShader> vertexShader) { mVertexShader = vertexShader; }
    /**
    * @brief �s�N�Z���V�F�[�_�[��ݒ肷��
    * @param pixelShader �s�N�Z���V�F�[�_�[
    */
    void setPixelShader(std::shared_ptr<PixelShader> pixelShader) { mPixelShader = pixelShader; }
protected:
    std::shared_ptr<VertexBuffer> mVertexBuffer;
    std::shared_ptr<IndexBuffer> mIndexBuffer;
    std::shared_ptr<VertexShader> mVertexShader;
    std::shared_ptr<PixelShader> mPixelShader;
};

} //Graphics 
} //Framework 
