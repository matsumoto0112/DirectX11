#pragma once
#include <unordered_map>

namespace Framework {
namespace Utility {

template<typename TKey, typename TValue>
static bool exist(const std::unordered_map<TKey, TValue>& m, const TKey& value);

template<typename TKey, typename TValue>
bool exist(const std::unordered_map<TKey, TValue>& m, const TKey& value) {
    return m.find(value) != m.end();
}

} //Utility 
} //Framework 