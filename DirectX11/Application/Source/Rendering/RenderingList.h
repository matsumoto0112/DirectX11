#pragma once

#include <vector>
#include "Framework/Graphics/Color4.h"
#include "Framework/Math/Matrix4x4.h"
#include "Framework/Graphics/Texture/Texture.h"
#include "Framework/Math/Rect.h"
#include "Framework/Math/MathUtility.h"
#include "Framework/Graphics/Shader/Effect.h"
// #include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/Transform.h"

/*
memo
描画するオブジェクトはこのリストに順次追加していく
描画時にはまずアルファ値を参照し、不透明オブジェクトを先に描画する
そのあと、透明のオブジェクトを奥から順に描画していく（この時ZDepthは切っておく）
これを実現するにはリスト構造が必要。
描画リストを取得する関数が呼ばれたときに描画リストを返す
その時、不透明オブジェクトだけを取得する、もしくは透明オブジェクトをソートされた状態で取得できる必要がある
追加はn個、ソートは1回、削除は全削除
マテリアルの構造をどうするか
アルファ値は参照したい
2D,3Dを気にしたくはない
IMaterial基底クラスを用意。
マテリアルに必須要素を用意するか？
マテリアルにすべての描画要素を詰め込みたい
マテリアルにシェーダーを持たせる
Transform,Colorは常に使用される
ただし、Transformは2D,3Dで違うものとする
マテリアルは複数個よく使われるものを作っておくが必要に応じて追加も可能とする
マテリアルはカメラを気にしないものとする
*/

/**
* @brief 描画の仕方定義
* @enum RenderType
*/
enum class RenderType {
    Opaque, //!< 不透明
    Transparency, //!< 透明
};

/**
* @class IMaterial
* @brief マテリアル基底クラス
*/
class IMaterial {
protected:
    using EffectPtr = std::shared_ptr<Framework::Graphics::Effect>;
public:
    /**
    * @brief コンストラクタ
    */
    IMaterial(EffectPtr effect, RenderType renderType = RenderType::Opaque)
        :mEffect(effect), mRenderType(renderType) { };
    /**
    * @brief デストラクタ
    */
    virtual ~IMaterial() = default;

    virtual void set() {
        auto cbManager = Framework::Utility::getConstantBufferManager();
        using Framework::Graphics::ConstantBufferParameterType;
        cbManager->setMatrix(ConstantBufferParameterType::World3D, mTransform.createSRTMatrix());
        cbManager->setColor(ConstantBufferParameterType::Color, mColor);
        mEffect->set();
    }
public:
    EffectPtr mEffect; //!< このマテリアルのシェーダー
    RenderType mRenderType; //!< 描画の仕方
    Framework::Utility::Transform mTransform; //!< マテリアルのトランスフォーム
    Framework::Graphics::Color4 mColor; //!< このマテリアルの色
};

/**
* @class TextureMaterial
* @brief discription
*/
class TextureMaterial : public IMaterial {
protected:
    using TexturePtr = std::shared_ptr<Framework::Graphics::Texture>;
public:
    /**
    * @brief コンストラクタ
    */
    TextureMaterial(EffectPtr effect, TexturePtr texture)
        :IMaterial(effect), mTexture(texture), mSrcRect({}) { };
    /**
    * @brief デストラクタ
    */
    virtual ~TextureMaterial() { };
public:
    TexturePtr mTexture;
    Framework::Math::Rect mSrcRect;
};

/**
* @class Renderable
* @brief 描画対象オブジェクト
*/
class Renderable {
    using MaterialPtr = std::shared_ptr<IMaterial>;
public:
    /**
    * @brief コンストラクタ
    */
    Renderable(MaterialPtr material)
        :mMaterial(material) { }
    /**
    * @brief デストラクタ
    */
    virtual ~Renderable() { }
    /**
    * @brief マテリアルを取得する
    */
    IMaterial* getMaterial() { return mMaterial.get(); }

    virtual void render() { mMaterial->set(); }
protected:
    MaterialPtr mMaterial;
};

/**
* @class RenderingList
* @brief 描画対象のリスト
*/
class RenderingList {
    using List = std::vector<Renderable*>;
public:
    /**
    * @brief コンストラクタ
    */
    RenderingList()
        :mOpaqueObjects(),
        mTransparencyObjects() { }
    /**
    * @brief デストラクタ
    */
    ~RenderingList() {
        List().swap(mOpaqueObjects);
        List().swap(mTransparencyObjects);
    }

    /**
    * @brief 描画対象リストに追加する
    */
    void add(Renderable* renderable) {
        if (renderable->getMaterial()->mRenderType == RenderType::Opaque) {
            mOpaqueObjects.emplace_back(renderable);
        }
        else {
            mTransparencyObjects.emplace_back(renderable);
        }
    }
    /**
    * @brief リストをクリアする
    */
    void clear() {
        mOpaqueObjects.clear();
        mTransparencyObjects.clear();
    }

    const List& getOpaqueList() const { return mOpaqueObjects; }
    const List& getTransparencyList() const { return mTransparencyObjects; }
private:
    List mOpaqueObjects; //!< 不透明オブジェクト
    List mTransparencyObjects; //!< 透明オブジェクト
};