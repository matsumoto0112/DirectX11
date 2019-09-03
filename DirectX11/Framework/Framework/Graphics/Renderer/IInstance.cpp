#include "IInstance.h"
#include "Framework/Utility/Wrap/DirectX.h"
#include "Framework/Utility/Wrap/OftenUsed.h"

namespace Framework {
namespace Graphics {

void IInstance::render(const Utility::Transform& transform) {
    Utility::getConstantBufferManager()->setMatrix(ConstantBufferParameterType::World, transform.createSRTMatrix());
    Utility::getConstantBufferManager()->send();
    mVIBuffer->render();
}

} //Graphics 
} //Framework 
