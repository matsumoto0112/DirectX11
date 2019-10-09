#pragma once
#include <string>
#include <fbxsdk.h>

namespace Framework {
namespace Utility {

/**
* @class FBXLoader
* @brief discription
*/
class FBXLoader final {
public:
    /**
    * @brief �R���X�g���N�^
    */
    FBXLoader(const std::string& filepath);
    /**
    * @brief �f�X�g���N�^
    */
    ~FBXLoader();
private:
    FbxManager* mManager;
};

} //Utility 
} //Framework 