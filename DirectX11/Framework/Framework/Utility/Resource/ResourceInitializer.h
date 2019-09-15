#pragma once
namespace Framework {
namespace Utility {

class ResourceManager;

/**
* @brief リソースストレージの初期化処理
*/
class ResourceInitializeOnStart {
public:
    /**
    * @brief コンストラクタ
    * @param resourceManager リソース管理者
    */
    ResourceInitializeOnStart(ResourceManager& resourceManager);
};

} //Utility 
} //Framework 
