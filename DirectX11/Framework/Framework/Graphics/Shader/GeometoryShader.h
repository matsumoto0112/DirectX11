#pragma once

#include <string>
#include "Framework/Graphics/Shader/ShaderBase.h"

namespace Framework {
namespace Graphics {
/**
* @class GeometoryShader
* @brief ジオメトリシェーダ
*/
class GeometoryShader : public ShaderBase {
public:
    /**
    * @brief コンストラクタ
    * @param filepath シェーダーファイルのパス
    */
    GeometoryShader(const std::string& filepath);
    /**
    * @brief デストラクタ
    */
    ~GeometoryShader();
    /**
    * @brief シェーダのセット
    */
    void set();
private:
    ComPtr<ID3D11GeometryShader> mGeometoryShader; //!< シェーダーのデータ
};

} //Graphics 
} //Framework 
