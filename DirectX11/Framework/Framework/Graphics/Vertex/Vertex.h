#pragma once

#include "Framework/Graphics/Color4.h"
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Vector3.h"
#include "Framework/Math/Vector4.h"

namespace Framework {
namespace Graphics {

struct OnlyPosition {
    Math::Vector4 pos;
};

/**
* @struct BaseVertex2D
* @brief 2D�p��{���_�N���X
*/
struct BaseVertex2D {
    Math::Vector4 pos; //!< ���_���W
    Math::Vector2 uv; //!< UV���W
};

/*
* @struct TextureVertex3D
* @brief 3D���_
*/
struct TextureVertex3D {
    Math::Vector4 pos; //!< ���W
    Math::Vector3 normal; //!< �@��
    Math::Vector2 uv; //!< UV���W
};

/**
* @struct MeshVertex
* @brief ���b�V�����_
*/
struct MeshVertex {
    Math::Vector4 pos; //!< ���W
    Math::Vector3 normal; //!< �@��
    Math::Vector2 uv; //UV���W
    Color4 color; //!< ���_�J���[
};

/**
* @struct AnimVert
* @brief �A�j���[�V�����t�����b�V�����_
*/
struct AnimVert {
    Math::Vector4 pos; //!< ���_���W
    Math::Vector3 normal; //!< �@��
    Math::Vector2 uv; //!< UV���W
    Color4 color; //!< ���_�J���[
    unsigned int index[4]; //!< �{�[���s��C���f�b�N�X
    float weight[4]; //!< �{�[���s��E�F�C�g
};

} //Graphics 
} //Framework