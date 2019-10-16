#include "ShaderBase.h"

std::string Framework::Graphics::ShaderBase::addExtendIfNotExist(const std::string& filepath) {
    size_t size = filepath.size();
    //ÉpÉXÇÃç≈å„Ç…".cso"Ç™Ç†ÇÈÇ»ÇÁÇªÇÃÇ‹Ç‹
    if (filepath.substr(size - 4) == ".cso") {
        return filepath;
    }
    return filepath + ".cso";
}
