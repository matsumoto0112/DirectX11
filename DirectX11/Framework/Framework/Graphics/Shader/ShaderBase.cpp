#include "ShaderBase.h"
#include "Framework/Utility/IO/ByteReader.h"

namespace Framework {
namespace Graphics {

Graphics::ShaderBase::ShaderBase()
    :mByteReader(std::make_unique<Utility::ByteReader>()) {}

} //Graphics 
} //Framework 
