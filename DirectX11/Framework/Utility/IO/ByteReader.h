#pragma once

#include <vector>
#include <string>
#include <Windows.h>

namespace Framework {
namespace Utility {

/**
* @class ByteReader
* @brief ファイルをバイトデータで読み込む
*/
class ByteReader {
public:
    /**
    * @brief コンストラクタ
    */
    ByteReader();
    /**
    * @brief デストラクタ
    */
    ~ByteReader();
    /**
    * @brief 読む
    * @param filepath ファイルパス
    * @return 読み込んだデータ
    */
    std::vector<BYTE> read(const std::string& filepath);
};

} //Utility 
} //Framework
