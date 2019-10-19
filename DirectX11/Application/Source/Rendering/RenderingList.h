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
�`�悷��I�u�W�F�N�g�͂��̃��X�g�ɏ����ǉ����Ă���
�`�掞�ɂ͂܂��A���t�@�l���Q�Ƃ��A�s�����I�u�W�F�N�g���ɕ`�悷��
���̂��ƁA�����̃I�u�W�F�N�g�������珇�ɕ`�悵�Ă����i���̎�ZDepth�͐؂��Ă����j
�������������ɂ̓��X�g�\�����K�v�B
�`�惊�X�g���擾����֐����Ă΂ꂽ�Ƃ��ɕ`�惊�X�g��Ԃ�
���̎��A�s�����I�u�W�F�N�g�������擾����A�������͓����I�u�W�F�N�g���\�[�g���ꂽ��ԂŎ擾�ł���K�v������
�ǉ���n�A�\�[�g��1��A�폜�͑S�폜
�}�e���A���̍\�����ǂ����邩
�A���t�@�l�͎Q�Ƃ�����
2D,3D���C�ɂ������͂Ȃ�
IMaterial���N���X��p�ӁB
�}�e���A���ɕK�{�v�f��p�ӂ��邩�H
�}�e���A���ɂ��ׂĂ̕`��v�f���l�ߍ��݂���
�}�e���A���ɃV�F�[�_�[����������
Transform,Color�͏�Ɏg�p�����
�������ATransform��2D,3D�ňႤ���̂Ƃ���
�}�e���A���͕����悭�g������̂�����Ă������K�v�ɉ����Ēǉ����\�Ƃ���
�}�e���A���̓J�������C�ɂ��Ȃ����̂Ƃ���
*/

/**
* @brief �`��̎d����`
* @enum RenderType
*/
enum class RenderType {
    Opaque, //!< �s����
    Transparency, //!< ����
};

/**
* @class IMaterial
* @brief �}�e���A�����N���X
*/
class IMaterial {
protected:
    using EffectPtr = std::shared_ptr<Framework::Graphics::Effect>;
public:
    /**
    * @brief �R���X�g���N�^
    */
    IMaterial(EffectPtr effect, RenderType renderType = RenderType::Opaque)
        :mEffect(effect), mRenderType(renderType) { };
    /**
    * @brief �f�X�g���N�^
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
    EffectPtr mEffect; //!< ���̃}�e���A���̃V�F�[�_�[
    RenderType mRenderType; //!< �`��̎d��
    Framework::Utility::Transform mTransform; //!< �}�e���A���̃g�����X�t�H�[��
    Framework::Graphics::Color4 mColor; //!< ���̃}�e���A���̐F
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
    * @brief �R���X�g���N�^
    */
    TextureMaterial(EffectPtr effect, TexturePtr texture)
        :IMaterial(effect), mTexture(texture), mSrcRect({}) { };
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~TextureMaterial() { };
public:
    TexturePtr mTexture;
    Framework::Math::Rect mSrcRect;
};

/**
* @class Renderable
* @brief �`��ΏۃI�u�W�F�N�g
*/
class Renderable {
    using MaterialPtr = std::shared_ptr<IMaterial>;
public:
    /**
    * @brief �R���X�g���N�^
    */
    Renderable(MaterialPtr material)
        :mMaterial(material) { }
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Renderable() { }
    /**
    * @brief �}�e���A�����擾����
    */
    IMaterial* getMaterial() { return mMaterial.get(); }

    virtual void render() { mMaterial->set(); }
protected:
    MaterialPtr mMaterial;
};

/**
* @class RenderingList
* @brief �`��Ώۂ̃��X�g
*/
class RenderingList {
    using List = std::vector<Renderable*>;
public:
    /**
    * @brief �R���X�g���N�^
    */
    RenderingList()
        :mOpaqueObjects(),
        mTransparencyObjects() { }
    /**
    * @brief �f�X�g���N�^
    */
    ~RenderingList() {
        List().swap(mOpaqueObjects);
        List().swap(mTransparencyObjects);
    }

    /**
    * @brief �`��Ώۃ��X�g�ɒǉ�����
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
    * @brief ���X�g���N���A����
    */
    void clear() {
        mOpaqueObjects.clear();
        mTransparencyObjects.clear();
    }

    const List& getOpaqueList() const { return mOpaqueObjects; }
    const List& getTransparencyList() const { return mTransparencyObjects; }
private:
    List mOpaqueObjects; //!< �s�����I�u�W�F�N�g
    List mTransparencyObjects; //!< �����I�u�W�F�N�g
};