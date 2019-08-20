#pragma once
#include "Graphics/Color4.h"

namespace Framework {
namespace Graphics {

struct MaterialCBufferStruct {
    Color4 ambient; //!< ��������
    Color4 diffuse; //!< �g�U����
    Color4 specular; //!< ���ʔ��� 
    float shininess; //!< �P�x
    float alpha; //!< �A���t�@�l
    float tr; //�����F
    bool illumuFlag; //!< �Ɩ����f��
};

} //Graphics 
} //Framework