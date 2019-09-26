#pragma once
#include "Framework/Define/Resource/PixelShader.h"
#include "Framework/Graphics/Shader/PixelShader.h"
#include "Framework/Utility/Resource/AbstractResourceStorage.h"

namespace Framework {
namespace Utility {

/**
* @class PixelShaderResourceStorage
* @brief ピクセルシェーダストレージ
*/
class PixelShaderResourceStorage : public AbstractResourceStorage<Define::PixelShaderType, Graphics::PixelShader> {
public:
    /**
    * @brief コンストラクタ
    */
    PixelShaderResourceStorage();
    /**
    * @brief デストラクタ
    */
    ~PixelShaderResourceStorage();
    /**
    * @brief リソースをインポートする
    */
    virtual void importResource(Define::PixelShaderType type) override;
};

} //Utility 
} //Framework 
