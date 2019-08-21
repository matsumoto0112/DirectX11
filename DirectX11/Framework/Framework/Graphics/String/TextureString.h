#pragma once

#include <memory>
#include <vector>
#include "Framework/Math/Vector2.h"

namespace Framework {
namespace Graphics {
class GraphicsDeviceManager;
class TextureChar;

/**
* @class TextureString
* @brief ������摜�N���X
*/
class TextureString {
public:
    /**
    * @brief �R���X�g���N�^
    * @param str �\�����镶����
    * @param fontSize �t�H���g�̑傫��
    * @param font �t�H���g�̎��
    */
    TextureString(const std::string& str, int fontSize, const std::string& font = "");
    /**
    * @brief �f�X�g���N�^
    */
    ~TextureString();
    /**
    * @brief ���W�̐ݒ�
    */
    void setPosition(const Math::Vector2& position);
    /**
    * @brief ���W�̎擾
    */
    const Math::Vector2& getPosition() const;
    void setString(const std::string& str);
    const std::string& getString() const { return mStr; }
    void setFontSize(int size);
    int getFontSize() const { return mFontSize; }
    void setFont(const std::string& font);
    const std::string& getFont() const { return mFont; }
    /**
    * @brief �`�悷��
    */
    void draw();
    void setZOrder(float z);
    float getZOrder() const;
private:
    void create();
private:
    std::string mStr;
    int mFontSize;
    std::string mFont;
    Math::Vector2 mPosition;
    std::vector<std::unique_ptr<TextureChar>> mTextureChars; //!< ������摜���X�g
};

} //Graphics
} //Framework 
