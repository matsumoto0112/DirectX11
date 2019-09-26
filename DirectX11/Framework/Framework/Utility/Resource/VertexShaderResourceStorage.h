#pragma once
#include <unordered_map>
#include "Framework/Define/Resource/VertexShader.h"
#include "Framework/Graphics/Shader/VertexShader.h"
#include "Framework/Utility/Resource/AbstractResourceStorage.h"

namespace Framework {
namespace Utility {

/**
* @class VertexShaderResourceStorage
* @brief 頂点シェーダストレージ
*/
class VertexShaderResourceStorage : public AbstractResourceStorage<Define::VertexShaderType, Graphics::VertexShader> {
public:
    /**
    * @brief コンストラクタ
    */
    VertexShaderResourceStorage();
    /**
    * @brief デストラクタ
    */
    ~VertexShaderResourceStorage();
    /**
    * @brief リソースをインポートする
    */
    virtual void importResource(Define::VertexShaderType type) override;
};

} //Utility 
} //Framework 
