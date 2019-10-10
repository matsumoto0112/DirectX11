#pragma once
#include <Windows.h>
#include "Framework/Utility/Singleton.h"
#include "Framework/Math/Vector2.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Define {

/**
* @class Config
* @brief �O���t�@�C���ˑ��ݒ�Ǘ��N���X
*/
class Config : public Utility::Singleton<Config> {
protected:
    /**
    * @brief �R���X�g���N�^
    */
    Config();
    /**
    * @brief �f�X�g���N�^
    */
    ~Config();
public:
    const Math::Vector2 getSize() const { return Math::Vector2(static_cast<float>(mWidth), static_cast<float>(mHeight)); };
private:
    PROPERTY_READONLY(UINT, mWidth, Width);
    PROPERTY_READONLY(UINT, mHeight, Height);
};

} //Define 
} //Framework 