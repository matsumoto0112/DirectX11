#pragma once

namespace Define {

/**
* @enum TextureType
* @brief �e�N�X�`����ޒ�`
*/
enum class TextureType {
    Smoke,
    Circle,
};

/**
* @class TextureName
* @brief �e�N�X�`���̃��\�[�X����`
*/
class TextureName {
public:
    static const std::string SMOKE;
    static const std::string CIRCLE;
};

} //Define 