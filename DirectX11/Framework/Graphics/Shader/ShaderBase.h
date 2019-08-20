#pragma once

#include <memory>
#include <d3d11.h>
#include <wrl/client.h>

namespace Framework {
namespace Utility {
class ByteReader;
} //Utility 

namespace Graphics {
class GraphicsDeviceManager;
class ResourceSetterToDevice;

/**
* @class ShaderBase
* @brief シェーダ基底クラス
*/
class ShaderBase {
public:
    /**
    * @brief コンストラクタ
    */
    ShaderBase();
    /**
    * @brief デストラクタ
    */
    virtual ~ShaderBase() = default;
    /**
    * @brief シェーダを使用する
    */
    virtual void set() = 0;
protected:
    using ByteReaderPtr = std::unique_ptr<Utility::ByteReader>;
    ByteReaderPtr mByteReader; //!< バイトデータ読み込み
};

} //Graphics 
} //Framework 
