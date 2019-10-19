#pragma once
#include "Framework/Graphics/ConstantBuffer/ConstantBufferStruct.h"
#include "Framework/Graphics/Resource/ShaderInputType.h"
#include "Framework/Utility/Debug.h"

namespace Framework {
    namespace Graphics {
        /**
        * @class ConstantBuffer
        * @brief �R���X�^���g�o�b�t�@
        */
        class ConstantBuffer {
        public:
            /**
            * @brief �R���X�g���N�^
            * @param graphicsDevice �O���t�B�b�N�f�o�C�X
            * @param inputType �ǂ̃V�F�[�_�ɒl��ݒ肷�邩
            * @param slotNum �V�F�[�_�̂ǂ̃X���b�g�ɒl��ݒ肷�邩
            */
            ConstantBuffer(ID3D11Device* device, UINT size, ShaderInputType inputType, UINT slotNumber);
            /**
            * @brief �f�X�g���N�^
            */
            virtual ~ConstantBuffer();

            void updateBuffer(ID3D11DeviceContext* context, void* data);
            /**
            * @brief �o�b�t�@�̒l��]������
            */
            void set(ID3D11DeviceContext* context);
            /**
            * @brief �o�b�t�@�̒l���N���A����
            */
            void clear(ID3D11DeviceContext* context);
        private:
            ComPtr<ID3D11Buffer> mConstantBuffer; //!< �R���X�^���g�o�b�t�@
            const ShaderInputType mInputType; //!< �ǂ̃V�F�[�_�[�Ƀf�[�^��]�����邩
            const UINT mRegisterNum; //!< �V�F�[�_�[�̓o�^�ԍ�
            const UINT mSize;
        };


    } //Graphics 
} //Framework