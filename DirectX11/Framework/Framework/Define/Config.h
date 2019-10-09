#pragma once
#include <Windows.h>
#include "Framework/Utility/Singleton.h"
#include "Framework/Math/Vector2.h"

namespace Framework {
namespace Define {

/**
* @class Config
* @brief �O���t�@�C���ˑ��ݒ�Ǘ��N���X
*/
class Config : public Utility::Singleton<Config> {
public:

protected:
    /**
    * @brief �R���X�g���N�^
    */
    Config();
    /**
    * @brief �f�X�g���N�^
    */
    ~Config();
    //private:
public:
    const Math::Vector2 getSize() const { return Math::Vector2(mWidth, mHeight); };
public:
    UINT mWidth;
    UINT mHeight;
};

} //Define 
} //Framework 