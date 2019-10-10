#pragma once
#include <d3d11.h>
#include <stdexcept>

namespace Framework {
namespace Graphics {

/**
* @brief HRESULT�𕶎���ɕϊ�����
*/
inline std::string HrToString(HRESULT hr) {
    char s_str[64] = {};
    sprintf_s(s_str, "HRESULT of 0x%08X", static_cast<UINT>(hr));
    return std::string(s_str);
}

/**
* @brief HRESULT��O�N���X
*/
class HrException : public std::runtime_error {
public:
    HrException(HRESULT hr) : std::runtime_error(HrToString(hr)), m_hr(hr) { }
    HRESULT Error() const { return m_hr; }
private:
    const HRESULT m_hr;
};

/**
* @brief HRESULT�����s���Ă������O���X���[����
*/
inline void throwIfFailed(HRESULT hr) {
    if (FAILED(hr)) {
        throw HrException(hr);
    }
}

} //Graphics 
} //Framework 