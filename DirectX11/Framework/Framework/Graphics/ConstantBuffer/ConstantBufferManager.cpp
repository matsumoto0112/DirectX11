#include "ConstantBufferManager.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBufferTypeManager.h"

namespace Framework {
namespace Graphics {

ConstantBufferManager::ConstantBufferManager()
    : mMatrixBufferManager(std::make_unique<ConstantBufferTypeManager<Math::Matrix4x4>>()),
    mFloatBufferManager(std::make_unique<ConstantBufferTypeManager<float>>()),
    mColorBufferManager(std::make_unique<ConstantBufferTypeManager<Color4>>()),
    mIntBufferManager(std::make_unique<ConstantBufferTypeManager<int>>()),
    mVector4BufferManager(std::make_unique<ConstantBufferTypeManager<Math::Vector4>>()) {
    setup();
}

ConstantBufferManager::~ConstantBufferManager() { }

void ConstantBufferManager::send() {
    mMVP3DCBuffer->sendBuffer();
    mMVP2DCBuffer->sendBuffer();
    mUVCBuffer->sendBuffer();
    mColorCBuffer->sendBuffer();
    mLightCBuffer->sendBuffer();
    mLightMatrixCBuffer->sendBuffer();
}

void ConstantBufferManager::setMatrix(ConstantBufferParameterType type, const Math::Matrix4x4& value) {
    mMatrixBufferManager->set(type, value.transpose());
}

void ConstantBufferManager::setFloat(ConstantBufferParameterType type, float value) {
    mFloatBufferManager->set(type, value);
}

void ConstantBufferManager::setColor(ConstantBufferParameterType type, const Color4& value) {
    mColorBufferManager->set(type, value);
}

void ConstantBufferManager::setInt(ConstantBufferParameterType type, int value) {
    mIntBufferManager->set(type, value);
}

void ConstantBufferManager::setBool(ConstantBufferParameterType type, bool value) { }

void ConstantBufferManager::setVector4(ConstantBufferParameterType type, const Math::Vector4& value) {
    mVector4BufferManager->set(type, value);
}

void ConstantBufferManager::clearBuffer() {
    mMVP3DCBuffer->clear();
    mMVP2DCBuffer->clear();
    mUVCBuffer->clear();
    mColorCBuffer->clear();
    mLightCBuffer->clear();
    mLightMatrixCBuffer->clear();
}

void ConstantBufferManager::setup() {
#define ADD_SEND_FUNC(manager, ParameterType,VariableType,buffer,Parameter) { \
        manager->add(ParameterType, [&](const VariableType& m) { \
            auto s = buffer->getData(); \
            s.##Parameter = m; \
            buffer->setBuffer(s); \
            }); \
    }

    ShaderInputType inputType = ShaderInputType::Vertex | ShaderInputType::Pixel | ShaderInputType::Geometory;
    mMVP3DCBuffer = std::make_unique<ConstantBuffer<MVPMatrix3DCBuffer>>(inputType, 0);
    ADD_SEND_FUNC(mMatrixBufferManager, ConstantBufferParameterType::World3D, Math::Matrix4x4, mMVP3DCBuffer, world);
    ADD_SEND_FUNC(mMatrixBufferManager, ConstantBufferParameterType::View3D, Math::Matrix4x4, mMVP3DCBuffer, view);
    ADD_SEND_FUNC(mMatrixBufferManager, ConstantBufferParameterType::Projection3D, Math::Matrix4x4, mMVP3DCBuffer, proj);

    mMVP2DCBuffer = std::make_unique<ConstantBuffer<MVPMatrix2DCBuffer>>(inputType, 1);
    ADD_SEND_FUNC(mMatrixBufferManager, ConstantBufferParameterType::World2D, Math::Matrix4x4, mMVP2DCBuffer, world);
    ADD_SEND_FUNC(mMatrixBufferManager, ConstantBufferParameterType::View2D, Math::Matrix4x4, mMVP2DCBuffer, view);
    ADD_SEND_FUNC(mMatrixBufferManager, ConstantBufferParameterType::Projection2D, Math::Matrix4x4, mMVP2DCBuffer, proj);

    mUVCBuffer = std::make_unique<ConstantBuffer<UVInfoCBuffer>>(inputType, 2);
    ADD_SEND_FUNC(mFloatBufferManager, ConstantBufferParameterType::UVLeft, float, mUVCBuffer, left);
    ADD_SEND_FUNC(mFloatBufferManager, ConstantBufferParameterType::UVTop, float, mUVCBuffer, top);
    ADD_SEND_FUNC(mFloatBufferManager, ConstantBufferParameterType::UVWidth, float, mUVCBuffer, width);
    ADD_SEND_FUNC(mFloatBufferManager, ConstantBufferParameterType::UVHeight, float, mUVCBuffer, height);

    mColorCBuffer = std::make_unique<ConstantBuffer<ColorCBuffer>>(inputType, 3);
    ADD_SEND_FUNC(mColorBufferManager, ConstantBufferParameterType::Color, Color4, mColorCBuffer, color);

    mLightCBuffer = std::make_unique<ConstantBuffer<LightCBuffer>>(inputType, 4);
    ADD_SEND_FUNC(mVector4BufferManager, ConstantBufferParameterType::DirectionalLightDirection, Math::Vector4, mLightCBuffer, direction);
    ADD_SEND_FUNC(mColorBufferManager, ConstantBufferParameterType::DirectionalLightColor, Color4, mLightCBuffer, color);

    mLightMatrixCBuffer = std::make_unique<ConstantBuffer<LightMatrixCBuffer>>(inputType, 7);
    ADD_SEND_FUNC(mMatrixBufferManager, ConstantBufferParameterType::LightView, Math::Matrix4x4, mLightMatrixCBuffer, lightView);
    ADD_SEND_FUNC(mMatrixBufferManager, ConstantBufferParameterType::LightProj, Math::Matrix4x4, mLightMatrixCBuffer, lightProj);
}

} //Graphics 
} //Framework
