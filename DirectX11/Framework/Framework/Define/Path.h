#pragma once

#include <string>
#include "Framework/Utility/Singleton.h"

namespace Define {
/**
* @class Path
* @brief 各種ファイルへのパスを定義
*/
class Path : public Framework::Utility::Singleton<Path> {
public:
    const std::string& exe() const { return mExe; }
    const std::string& resource() const { return mResource; }
    const std::string& texture() const { return mTexture; }
    const std::string& shader() const { return mShader; }
    const std::string& model() const { return mModel; }
    const std::string& fbxModel() const { return mFBXModel; }
    const std::string& objModel() const { return mOBJModel; }
private:
    std::string mExe;
    std::string mResource; //!< リソースフォルダへのパス
    std::string mTexture; //!< テクスチャのルートフォルダへのパス
    std::string mShader; //!< シェーダファイルへのパス
    std::string mModel; //!< モデルデータファイルへのパス
    std::string mFBXModel; //!< FBXモデルへのパス
    std::string mOBJModel; //!< OBJモデルへのパス
protected:
    Path();
    ~Path();
};
} //Define 
