#pragma once

#include "Framework/Graphics/Color4.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBufferParameterType.h"
#include "Framework/Math/Matrix4x4.h"
#include "Framework/Math/Rect.h"

namespace Framework {
namespace Graphics {

template <class T>
class ConstantBufferTypeManager;
struct MVPMatrixCBufferStruct;
struct UVInfoCBufferStruct;
struct ColorCBufferStruct;
struct MaterialCBufferStruct;
struct CameraNumCBufferStruct;

/**
* @class ConstantBufferManager
* @brief �R���X�^���g�o�b�t�@�Ǘ���
*/
class ConstantBufferManager {
public:
    /**
    * @brief �R���X�g���N�^
    */
    ConstantBufferManager();
    /**
    * @brief �f�X�g���N�^
    */
    ~ConstantBufferManager();
    /**
    * @brief �f�[�^�̓]��
    */
    void send();
    /**
    * @brief �s��̐ݒ�
    * @param type �]����
    * @param value �]������f�[�^
    */
    void setMatrix(ConstantBufferParameterType type, const Math::Matrix4x4& value);
    /**
    * @brief Float�̐ݒ�
    * @param type �]����
    * @param value �]������f�[�^
    */
    void setFloat(ConstantBufferParameterType type, float value);
    /**
    * @brief �F�̐ݒ�
    * @param type �]����
    * @param value �]������f�[�^
    */
    void setColor(ConstantBufferParameterType type, const Color4& value);
    /**
    * @brief Int�̐ݒ�
    * @param type �]����
    * @param value �]������f�[�^
    */
    void setInt(ConstantBufferParameterType type, int value);
    /**
    * @brief Bool�̐ݒ�
    * @param type �]����
    * @param value �]������f�[�^
    */
    void setBool(ConstantBufferParameterType type, bool value);
    /**
    * @brief ��`�̐ݒ�
    * @param type �]����
    * @param value �]������f�[�^
    */
    void setRect(ConstantBufferParameterType type, const Math::Rect& value);
    /**
    * @brief �\���̂̐ݒ�
    * @tparam T �]������\����
    * @param type �]����
    */
    template <class T>
    void setStruct(const T& value);
    void clearBuffer();
private:
    /**
    * @brief �����ݒ�
    */
    void setup();
private:
    std::unique_ptr<ConstantBuffer<MVPMatrixCBufferStruct>> mMVPCBuffer; //!< MVP�s��p�R���X�^���g�o�b�t�@
    std::unique_ptr<ConstantBuffer<UVInfoCBufferStruct>> mUVCBuffer; //!< UV�p�R���X�^���g�o�b�t�@
    std::unique_ptr<ConstantBuffer<ColorCBufferStruct>> mColorCBuffer; //!< �F�p�R���X�^���g�o�b�t�@
    std::unique_ptr<ConstantBuffer<MaterialCBufferStruct>> mMaterial; //!< �}�e���A���p�R���X�^���g�o�b�t�@
    std::unique_ptr<ConstantBuffer<CameraNumCBufferStruct>> mCameraCBuffer; //!< �J�����p�R���X�^���g�o�b�t�@

    std::unique_ptr<ConstantBufferTypeManager<Math::Matrix4x4>> mMatrixBufferManager; //!< �s��p�o�b�t�@�]���Ǘ���
    std::unique_ptr<ConstantBufferTypeManager<float>> mFloatBufferManager; //!< Float�p�o�b�t�@�]���Ǘ���
    std::unique_ptr<ConstantBufferTypeManager<Math::Rect>> mRectBufferManager; //!< ��`�p�o�b�t�@�]���Ǘ���
    std::unique_ptr<ConstantBufferTypeManager<Color4>> mColorBufferManager; //!< �F�p�o�b�t�@�]���Ǘ���
    std::unique_ptr<ConstantBufferTypeManager<int>> mIntBufferManager; //!< �����l�p�o�b�t�@�]���Ǘ���
};

template<class T>
inline void ConstantBufferManager::setStruct(const T& value) {
    static_assert(false);
}

} //Graphics 
} //Framework