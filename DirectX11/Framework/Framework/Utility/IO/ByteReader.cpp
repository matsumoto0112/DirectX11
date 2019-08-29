#include "ByteReader.h"
#include <atlstr.h>
#include <assert.h>
#include <stdio.h>
#include "Framework/Utility/Debug.h"

namespace Framework {
namespace Utility {

ByteReader::ByteReader(const std::string& filepath) {
    FILE* fp;
    //バイナリデータでファイルを開く
    int ret = fopen_s(&fp, filepath.c_str(), "rb");
    MY_ASSERTION(ret == 0, filepath + "が開けませんでした。");
    fseek(fp, 0, SEEK_END);
    //配列のサイズをデータの大きさにする
    mData = std::vector<BYTE>(ftell(fp));
    fseek(fp, 0, SEEK_SET);
    fread(mData.data(), mData.size(), 1, fp);
    fclose(fp);
}

ByteReader::~ByteReader() {}

std::vector<BYTE> ByteReader::get() {
    return mData;
}

} //Utility 
} //Framework
