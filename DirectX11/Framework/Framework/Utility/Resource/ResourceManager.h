#pragma once
#include <memory>
#include "Framework/Utility/Singleton.h"
#include "Framework/Utility/Resource/FBXModelResourceStorage.h"
#include "Framework/Utility/Resource/GeometoryShaderResourceStorage.h"
#include "Framework/Utility/Resource/PixelShaderResourceStorage.h"
#include "Framework/Utility/Resource/TextureResourceStorage.h"
#include "Framework/Utility/Resource/VertexShaderResourceStorage.h"

namespace Framework {
namespace Utility {

/**
* @class ResourceManager
* @brief ���\�[�X�Ǘ�
*/
class ResourceManager : public Singleton<ResourceManager> {
public:
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~ResourceManager();
    /**
    * @brief ���_�V�F�[�_�Ǘ��҂̎擾
    */
    VertexShaderResourceStorage* getVertexShader() const { return mVertexShaders.get(); }
    /**
    * @brief �W�I���g���V�F�[�_�Ǘ��҂̎擾
    */
    GeometoryShaderResourceStorage* getGeometoryShader() const { return mGeometoryShaders.get(); }
    /**
    * @brief �s�N�Z���V�F�[�_�Ǘ��҂̎擾
    */
    PixelShaderResourceStorage* getPixelShader() const { return mPixelShaders.get(); }
    /**
    * @brief FBX���f���Ǘ��҂̎擾
    */
    FBXModelResourceStorage* getFBXModel() const { return mFBXModel.get(); }
    /**
    * @brief �e�N�X�`���Ǘ��҂̎擾
    */
    TextureResourceStorage* getTexture() const { return mTexture.get(); }
protected:
    /**
    * @brief �R���X�g���N�^
    */
    ResourceManager();
private:
    std::unique_ptr<VertexShaderResourceStorage> mVertexShaders;
    std::unique_ptr<GeometoryShaderResourceStorage> mGeometoryShaders;
    std::unique_ptr<PixelShaderResourceStorage> mPixelShaders;
    std::unique_ptr<FBXModelResourceStorage> mFBXModel;
    std::unique_ptr<TextureResourceStorage> mTexture;
};

} //Utility 
} //Framework 
