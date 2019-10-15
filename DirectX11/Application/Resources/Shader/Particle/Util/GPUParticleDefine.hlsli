#ifndef INCLUDE_PARTICLE_GPUPARTICLEDEFINE_HLSLI
#define INCLUDE_PARTICLE_GPUPARTICLEDEFINE_HLSLI

/**
* @def RANDOM_MAX
* @brief �����e�[�u���̒���
*/
#define RANDOM_MAX 65535 

StructuredBuffer<float> randomTable : register(t0); //!< �����e�[�u��
RWByteAddressBuffer randomSeed : register(u0); //!< �����̃V�[�h�l

/**
* @brief �p�[�e�B�N���Ɏg�p����O���[�o���f�[�^
*/
cbuffer GlobalData : register(b0)
{
    int emitIndex; //!< ��������C���f�b�N�X
    float elapsedTime; //!< �o�ߎ���
    float deltaTime; //!< �O�t���[������̍�������
};

#endif // INCLUDE_PARTICLE_GPUPARTICLEDEFINE_HLSLI