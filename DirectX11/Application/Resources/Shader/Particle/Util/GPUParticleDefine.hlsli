#ifndef INCLUDE_PARTICLE_GPUPARTICLEDEFINE_HLSLI
#define INCLUDE_PARTICLE_GPUPARTICLEDEFINE_HLSLI

/**
* @def RANDOM_MAX
* @brief 乱数テーブルの長さ
*/
#define RANDOM_MAX 65535 

StructuredBuffer<float> randomTable : register(t0); //!< 乱数テーブル
RWByteAddressBuffer randomSeed : register(u0); //!< 乱数のシード値

/**
* @brief パーティクルに使用するグローバルデータ
*/
cbuffer GlobalData : register(b0)
{
    int emitIndex; //!< 生成するインデックス
    float elapsedTime; //!< 経過時間
    float deltaTime; //!< 前フレームからの差分時間
};

#endif // INCLUDE_PARTICLE_GPUPARTICLEDEFINE_HLSLI