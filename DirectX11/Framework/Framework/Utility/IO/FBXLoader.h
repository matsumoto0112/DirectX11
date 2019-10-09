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
    * @brief コンストラクタ
    */
    FBXLoader(const std::string& filepath);
    /**
    * @brief デストラクタ
    */
    ~FBXLoader();
private:
    FbxManager* mManager;
};

} //Utility 
} //Framework 