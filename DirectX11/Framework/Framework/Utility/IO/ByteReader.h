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
    * @param filepath �t�@�C���p�X
    */
    ByteReader(const std::string& filepath);
    /**
    * @brief �f�X�g���N�^
    */
    ~ByteReader();
    /**
    * @brief �f�[�^���擾����
    * @return �ǂݍ��񂾃f�[�^��Ԃ�
    */
    std::vector<BYTE> get();
private:
    std::vector<BYTE> mData;
};

} //Utility 
} //Framework
