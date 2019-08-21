#pragma once

#include <string>
#include "Framework/Utility/Singleton.h"

namespace Define {
/**
* @class Path
* @brief �e��t�@�C���ւ̃p�X���`
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
    std::string mResource; //!< ���\�[�X�t�H���_�ւ̃p�X
    std::string mTexture; //!< �e�N�X�`���̃��[�g�t�H���_�ւ̃p�X
    std::string mShader; //!< �V�F�[�_�t�@�C���ւ̃p�X
    std::string mModel; //!< ���f���f�[�^�t�@�C���ւ̃p�X
    std::string mFBXModel; //!< FBX���f���ւ̃p�X
    std::string mOBJModel; //!< OBJ���f���ւ̃p�X
protected:
    Path();
    ~Path();
};
} //Define 
