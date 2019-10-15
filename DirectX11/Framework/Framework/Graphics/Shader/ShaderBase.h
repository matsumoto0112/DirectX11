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
    ShaderBase() { }
    /**
    * @brief デストラクタ
    */
    virtual ~ShaderBase() = default;
    /**
    * @brief シェーダを使用する
    */
    virtual void set() = 0;
protected:
    /**
    * @brief パスの最後に拡張子がなければ追加する
    */
    std::string addExtendIfNotExist(const std::string& filepath);
};

} //Graphics 
} //Framework 
