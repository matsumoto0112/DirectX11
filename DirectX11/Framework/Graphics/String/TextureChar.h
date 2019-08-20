
#include <memory>
#include "Graphics/Sprite/Sprite2D.h"
#include "Math/IntVector2.h"

namespace Framework {
namespace Graphics {

/**
* @class TextureChar
* @brief 一文字分のテクスチャ
*/
class TextureChar : public Sprite2D {
    using IntVec2 = Math::IntVector2;
public:
    /**
    * @brief コンストラクタ
    * @param c 表示する1文字
    * @param fontSize フォントの大きさ
    * @param font フォントの種類
    */
    TextureChar( const char* c, int fontSize, const std::string& font);
    /**
    * @brief デストラクタ
    */
    virtual ~TextureChar();
    /**
    * @brief 描画する
    */
    virtual void draw() override;
    float getDisplayWidth() const;
    float getRightPositionX() const;
    Math::Vector2 getRightPosition() const;
private:
    IntVec2 mOffset;
    IntVec2 mBmpSize;
    IntVec2 mMargin;
};
} //Graphics
} //Framework 
