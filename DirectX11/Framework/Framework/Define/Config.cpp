#include "Config.h"
#include "Framework/Define/Path.h"

namespace Framework {
namespace Define {

Config::Config() {
    std::string path = Path::getInstance()->exe() + "/../config.ini";
    mWidth = GetPrivateProfileInt("Window", "Width", 0, path.c_str());
    mHeight = GetPrivateProfileInt("Window", "Height", 0, path.c_str());
}

Config::~Config() { }

} //Define
} //Framework 
