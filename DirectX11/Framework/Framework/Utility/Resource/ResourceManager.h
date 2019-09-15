#pragma once
#include <memory>
#include "Framework/Utility/Singleton.h"
#include "Framework/Utility/Resource/FBXModelResourceStorage.h"
#include "Framework/Utility/Resource/VertexShaderResourceStorage.h"
#include "Framework/Utility/Resource/PixelShaderResourceStorage.h"

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
    VertexShaderResourceStorage* getVertexShader() { return mVertexShaders.get(); }
    /**
    * @brief �s�N�Z���V�F�[�_�Ǘ��҂̎擾
    */
    PixelShaderResourceStorage* getPixelShader() { return mPixelShaders.get(); }
    /**
    * @brief FBX���f���Ǘ��҂̎擾
    */
    FBXModelResourceStorage* getFBXModel() { return mFBXModel.get(); }
protected:
    /**
    * @brief �R���X�g���N�^
    */
    ResourceManager();
private:
    std::unique_ptr<VertexShaderResourceStorage> mVertexShaders;
    std::unique_ptr<PixelShaderResourceStorage> mPixelShaders;
    std::unique_ptr<FBXModelResourceStorage> mFBXModel;
};

} //Utility 
} //Framework 
