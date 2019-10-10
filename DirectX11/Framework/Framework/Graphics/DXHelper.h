#pragma once
#include <d3d11.h>
#include <stdexcept>

namespace Framework {
namespace Graphics {

/**
* @brief HRESULTを文字列に変換する
*/
inline std::string HrToString(HRESULT hr) {
    char s_str[64] = {};
    sprintf_s(s_str, "HRESULT of 0x%08X", static_cast<UINT>(hr));
    return std::string(s_str);
}

/**
* @brief HRESULT例外クラス
*/
class HrException : public std::runtime_error {
public:
    HrException(HRESULT hr) : std::runtime_error(HrToString(hr)), m_hr(hr) { }
    HRESULT Error() const { return m_hr; }
private:
    const HRESULT m_hr;
};

/**
* @brief HRESULTが失敗していたら例外をスローする
*/
inline void throwIfFailed(HRESULT hr) {
    if (FAILED(hr)) {
        throw HrException(hr);
    }
}

} //Graphics 
} //Framework 