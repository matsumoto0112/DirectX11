#pragma once
#include "Framework/Define/Resource/GeometoryShader.h"
#include "Framework/Graphics/Shader/GeometoryShader.h"
#include "Framework/Utility/Resource/AbstractResourceStorage.h"

namespace Framework {
namespace Utility {

/**
* @class GeometoryShaderResourceStorage
* @brief ジオメトリシェーダストレージ
*/
class GeometoryShaderResourceStorage : public AbstractResourceStorage<Define::GeometoryShader, Graphics::GeometoryShader> {
public:
    /**
    * @brief コンストラクタ
    */
    GeometoryShaderResourceStorage();
    /**
    * @brief デストラクタ
    */
    ~GeometoryShaderResourceStorage();
    /**
    * @brief リソースをインポートする
    */
    virtual void importResource(Define::GeometoryShader type) override;
};

} //Utility 
} //Framework 
