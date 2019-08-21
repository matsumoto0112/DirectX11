#pragma once

#include <vector>
#include <string>
#include <Windows.h>

namespace Framework {
namespace Utility {

/**
* @class ByteReader
* @brief �t�@�C�����o�C�g�f�[�^�œǂݍ���
*/
class ByteReader {
public:
    /**
    * @brief �R���X�g���N�^
    */
    ByteReader();
    /**
    * @brief �f�X�g���N�^
    */
    ~ByteReader();
    /**
    * @brief �ǂ�
    * @param filepath �t�@�C���p�X
    * @return �ǂݍ��񂾃f�[�^
    */
    std::vector<BYTE> read(const std::string& filepath);
};

} //Utility 
} //Framework
