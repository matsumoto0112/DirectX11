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
    * @param filepath ファイルパス
    */
    ByteReader(const std::string& filepath);
    /**
    * @brief デストラクタ
    */
    ~ByteReader();
    /**
    * @brief データを取得する
    * @return 読み込んだデータを返す
    */
    std::vector<BYTE> get();
private:
    std::vector<BYTE> mData;
};

} //Utility 
} //Framework
