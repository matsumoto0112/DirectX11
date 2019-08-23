#pragma once
#include <memory>
#include <unordered_map>
#include "Framework/Define/Render/LightType.h"
#include "Framework/Graphics/Light/DirectionalLight.h"

namespace Framework {
namespace Graphics {

/**
* @class LightManager
* @brief discription
*/
class LightManager {
private:
    using DirectionalLightPtr = std::shared_ptr<DirectionalLight>;
    using DirectionalLightMap = std::unordered_map<Define::DirectionalLightType, DirectionalLightPtr >;
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
    DirectionalLightPtr addDirectionalLight(Define::DirectionalLightType key, const Math::Vector3& direction, const Color4& color);
    void set();
private:
    DirectionalLightMap mDirectionalLights;
};

} //Graphics 
} //Framework 