#pragma once

#include <string>
#include "Framework/Graphics/Shader/ShaderBase.h"
#include "Framework/Graphics/Shader/GeometoryShaderData.h"

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
    * @param filename シェーダファイル名
    */
    GeometoryShader(const std::string& filename);
    /**
    * @brief デストラクタ
    */
    ~GeometoryShader();
    /**
    * @brief シェーダのセット
    */
    void set();
private:
    /**
    * @brief シェーダの作成
    * @param name シェーダファイル名
    */
    void create(const std::string& name);
private:
    std::unique_ptr<GeometoryShaderData> mShaderData; //!< シェーダーのデータ
};

} //Graphics 
} //Framework 
