#pragma once
#include <Windows.h>
#include "Framework/Utility/Singleton.h"

namespace Framework {
namespace Define2 {

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
    UINT mWidth;
    UINT mHeight;
};

} //Define2 
} //Framework 