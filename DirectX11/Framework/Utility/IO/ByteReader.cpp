#include "ByteReader.h"
#include <atlstr.h>
#include <assert.h>
#include <stdio.h>
#include "Utility/Debug.h"

namespace Framework {
namespace Utility {

ByteReader::ByteReader() {}

ByteReader::~ByteReader() {}

std::vector<BYTE> ByteReader::read(const std::string& filepath) {
    FILE* fp;
    //バイナリデータでファイルを開く
    int ret = fopen_s(&fp, filepath.c_str(), "rb");
    MY_ASSERTION(ret == 0, filepath + "が開けませんでした。");
    fseek(fp, 0, SEEK_END);
    //配列のサイズをデータの大きさにする
    std::vector<BYTE> byteVector(ftell(fp));
    fseek(fp, 0, SEEK_SET);
    fread(byteVector.data(), byteVector.size(), 1, fp);
    fclose(fp);

    return byteVector;
}

} //Utility 
} //Framework
