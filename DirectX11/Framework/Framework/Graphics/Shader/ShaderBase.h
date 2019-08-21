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
* @brief �V�F�[�_���N���X
*/
class ShaderBase {
public:
    /**
    * @brief �R���X�g���N�^
    */
    ShaderBase();
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~ShaderBase() = default;
    /**
    * @brief �V�F�[�_���g�p����
    */
    virtual void set() = 0;
protected:
    using ByteReaderPtr = std::unique_ptr<Utility::ByteReader>;
    ByteReaderPtr mByteReader; //!< �o�C�g�f�[�^�ǂݍ���
};

} //Graphics 
} //Framework 
