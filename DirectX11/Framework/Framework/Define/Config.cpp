#include "Config.h"
#include "Framework/Define/Path.h"

namespace Framework {
namespace Define2 {

Config::Config() {
    std::string path = Define::Path::getInstance().exe() + "/../config.ini";
    mWidth = GetPrivateProfileInt("Window", "Width", 0, path.c_str());
    mHeight = GetPrivateProfileInt("Window", "Height", 600, path.c_str());
}

Config::~Config() { }

} //Define2
} //Framework 
