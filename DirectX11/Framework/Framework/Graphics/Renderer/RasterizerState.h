#pragma once

namespace Framework {
namespace Graphics {

/**
* @class RasterizerState
* @brief ���X�^���C�U�ݒ�
*/
class RasterizerState {
public:
    /**
    * @brief �R���X�g���N�^
    */
    RasterizerState(const D3D11_RASTERIZER_DESC* desc);
    /**
    * @brief �f�X�g���N�^
    */
    ~RasterizerState();
    /**
    * @brief ���X�^���C�U���R���e�L�X�g�ɃZ�b�g����
    */
    void set();
    /**
    * @brief �R���e�L�X�g�̏�Ԃ��N���A����
    */
    void clearState();
private:
    ComPtr<ID3D11RasterizerState> mRasterizer;
};

} //Graphics 
} //Framework 