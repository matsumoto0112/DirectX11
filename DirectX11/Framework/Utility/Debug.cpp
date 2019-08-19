#include "Debug.h"
#include <crtdbg.h>
#include <atlstr.h>
#include <sstream>

namespace Framework {
namespace Utility {

void errorWindow(bool condition, const std::string& message) {
    if (condition)return;
}

void Debug::assertion(const std::string& funcName, int line,
    bool condition, const std::string& message) {
    _ASSERT_EXPR(condition, CStringW(errorMessage(funcName, line, message).c_str()));
}

void Debug::debugLog(const std::string& funcName, int line, const std::string& message) {
    _RPT0(_CRT_WARN, errorMessage(funcName, line, message).c_str());
}

void Debug::errorWindow(const std::string& funcName, int line,
    bool condition, const std::string& message) {
    if (condition)return;
    std::string mes;
#if _DEBUG
    mes = errorMessage(funcName, line, message);
#else
    mes = message;
#endif
#if UNICODE
    CStringW wMes;
    wMes.Format(_T("%s"), mes);
    MessageBox(nullptr, wMes, TEXT("エラー"), MB_ICONINFORMATION);
#else
    MessageBox(nullptr, mes.c_str(), TEXT("エラー"), MB_ICONINFORMATION);
#endif
    exit(-1);
}

std::string Debug::errorMessage(const std::string& funcName,
    int line, const std::string& message) {
    return (StringBuilder(funcName) << " " << line << ":" << message << "\n");
}

Debug::Debug() {}

Debug::~Debug() {}

} //Utility
} //Framework
