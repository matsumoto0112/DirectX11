#include "ShaderBase.h"

std::string Framework::Graphics::ShaderBase::addExtendIfNotExist(const std::string& filepath) {
    int lastCSO = filepath.rfind(".cso");
    int size = filepath.size();
    //パスの最後に".cso"があるならそのまま
    if (lastCSO == size - 4) {
        return filepath;
    }
    return filepath + ".cso";
}
