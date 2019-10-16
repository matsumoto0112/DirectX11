#include "ShaderBase.h"

std::string Framework::Graphics::ShaderBase::addExtendIfNotExist(const std::string& filepath) {
    size_t size = filepath.size();
    //�p�X�̍Ō��".cso"������Ȃ炻�̂܂�
    if (filepath.substr(size - 4) == ".cso") {
        return filepath;
    }
    return filepath + ".cso";
}
