#include "ShaderBase.h"

std::string Framework::Graphics::ShaderBase::addExtendIfNotExist(const std::string& filepath) {
    int lastCSO = filepath.rfind(".cso");
    int size = filepath.size();
    //�p�X�̍Ō��".cso"������Ȃ炻�̂܂�
    if (lastCSO == size - 4) {
        return filepath;
    }
    return filepath + ".cso";
}
