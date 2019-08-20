#pragma once

#include <string>
#include "Utility/StringBuilder.h"
#include "Utility/Singleton.h"

/**
* @def VisualStudioの出力にログ出力
* @param mes 表示するメッセージ
*/
#define MY_DEBUG_LOG(mes) Framework::Utility::Debug::getInstance().debugLog(__FUNCTION__,__LINE__, mes)

/**
* @def アサーション
* @param cond 条件式
* @param mes condがfalseの時に表示するメッセージ
*/
#define MY_ASSERTION(cond,mes) Framework::Utility::Debug::getInstance().assertion(__FUNCTION__,__LINE__,cond, mes);

/**
* @def エラーウィンドウの表示
* @param cond 条件式
* @param mes condがfalseの時に表示するメッセージ
* @details デバッグ時にはメッセージとともに発生した関数名、行番号が表示される
*/
#define MY_ERROR_WINDOW(cond,mes) Framework::Utility::Debug::getInstance().errorWindow(__FUNCTION__,__LINE__,cond,mes);

/**
* @def 条件を満たしていたらVisualStudioの出力にログ出力
* @param cond 条件式
* @param mes 表示するメッセージ
*/
#define MY_DEBUG_LOG_IF(cond,mes) if((cond)) MY_DEBUG_LOG(mes)

namespace Framework {
namespace Utility {
class Debug : public Singleton<Debug> {
public:
    /**
    * @brief アサーション
    * @param funcName 関数名
    * @param line 発生した行
    * @param condition 条件
    * @param message エラーメッセージ
    */
    void assertion(const std::string& funcName, int line,
        bool condition, const std::string& message);
    /**
    * @brief ログ出力
    * @param funcName 関数名
    * @param line 発生した行
    * @param message 出力内容
    */
    void debugLog(const std::string& funcName, int line, const std::string& message);
    /**
    * @brief エラーウィンドウの表示
    * @param funcName 関数名
    * @param line 発生した行
    * @param condition 条件式
    * @param message エラーメッセージ
    */
    void errorWindow(const std::string& funcName, int line,
        bool condition, const std::string& message);
    /**
    * @brief エラーメッセージの作成
    * @param funcName 関数名
    * @param line 発生した行
    * @param message 実際のエラーメッセージ
    * @return [funcName line:message]の形式のメッセージを返す
    */
    std::string errorMessage(const std::string& funcName, int line,
        const std::string& message);
protected:
    /**
    * @brief コンストラクタ
    */
    Debug();
    /**
    * @brief デストラクタ
    */
    ~Debug();
};

} //Utility
} //Framework