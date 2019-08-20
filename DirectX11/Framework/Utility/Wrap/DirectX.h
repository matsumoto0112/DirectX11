#pragma once
#include <d3d11.h>

namespace Framework {
namespace Utility {

/**
* @brief デバイスの取得
*/
ID3D11Device* getDevice();

/**
* @brief デバイスコンテキストの取得
*/
ID3D11DeviceContext* getContext();


} //Utility 
} //Framework 