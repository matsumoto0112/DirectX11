#pragma once
#include <memory>
#include <unordered_map>
#include "Framework/Define/Render/LightType.h"
#include "Framework/Graphics/Light/DirectionalLight.h"
#include "Framework/Graphics/Light/PointLight.h"

namespace Framework {
namespace Graphics {

/**
* @class LightManager
* @brief discription
*/
class LightManager {
private:
    using DirectionalLightPtr = std::shared_ptr<DirectionalLight>;
    using DirectionalLightMap = std::unordered_map<Define::DirectionalLightType, DirectionalLightPtr>;
    using PointLightPtr = std::shared_ptr<PointLight>;
    using PointLightMap = std::unordered_map<Define::PointLightType, PointLightPtr>;
public:
    /**
    * @brief �R���X�g���N�^
    */
    LightManager();
    /**
    * @brief �f�X�g���N�^
    */
    ~LightManager();
    /**
    * @brief �f�B���N�V���i�����C�g�̒ǉ�
    * @param key ���C�g����ӂɓ��肷��L�[
    * @param direction ����
    * @param color �F
    */
    DirectionalLightPtr addDirectionalLight(
        Define::DirectionalLightType key, const Math::Vector3& direction, const Color4& color);
    /**
    * @brief �|�C���g���C�g�̒ǉ�
    * @param key ���C�g����ӂɓ��肷��L�[
    * @param position ���W
    * @param color �F
    * @param R �ő哞�B����
    * @param A ������
    */
    PointLightPtr addPointLight(
        Define::PointLightType key, const Math::Vector3& position, const Color4& color, float R, float A);

    void set();
private:
    DirectionalLightMap mDirectionalLights;
    PointLightMap mPointLights;
};

} //Graphics 
} //Framework 