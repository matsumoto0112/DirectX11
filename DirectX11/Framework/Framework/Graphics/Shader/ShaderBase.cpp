#include "ShaderBase.h"

std::string Framework::Graphics::ShaderBase::addExtendIfNotExist(const std::string& filepath) {
    size_t size = filepath.size();
    //パスの最後に".cso"があるならそのまま
    if (filepath.substr(size - 4) == ".cso") {
        return filepath;
    }
    return filepath + ".cso";
}
