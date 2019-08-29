#pragma once

namespace Framework {
namespace Graphics {

/**
* @class ShaderBase
* @brief シェーダ基底クラス
*/
class ShaderBase {
public:
    /**
    * @brief コンストラクタ
    */
    ShaderBase() {}
    /**
    * @brief デストラクタ
    */
    virtual ~ShaderBase() = default;
    /**
    * @brief シェーダを使用する
    */
    virtual void set() = 0;
};

} //Graphics 
} //Framework 
