#include "SpriteRenderer.h"
#include <vector>
#include <d3d11.h>
#include "Framework/Define/Path.h"
#include "Framework/Graphics/Buffer/VertexBuffer.h"
#include "Framework/Graphics/Buffer/IndexBuffer.h"
#include "Framework/Graphics/Vertex/Vertex.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "Framework/Graphics/RenderingManager.h"
#include "Framework/Graphics/Shader/Effect.h"
#include "Framework/Graphics/Resource/ShaderInputType.h"
#include "Framework/Graphics/Sprite/Sprite2D.h"
#include "Framework/Graphics/Sprite/Sprite3D.h"
#include "Framework/Graphics/Texture/Sampler.h"
#include "Framework/Graphics/Texture/Texture.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Renderer/PrimitiveVertex.h"
#include "Framework/Graphics/Desc/BlendStateDesc.h"
#include "Framework/Graphics/Desc/RasterizerStateDesc.h"

namespace Framework {
    namespace Graphics {
        //コンストラクタ
        SpriteRenderer::SpriteRenderer() {
            //描画対象のポリゴン生成
            std::vector<BaseVertex2D> vertices(4);
            auto positions = PrimitiveVertex::quadPosition();
            auto uvs = PrimitiveVertex::quadUV();
            for (int i = 0; i < vertices.size(); i++) {
                vertices[i].pos = positions[i];
                vertices[i].uv = uvs[i];
            }
            mVertexBuffer = std::make_unique<VertexBuffer>(vertices);
            mIndexBuffer = std::make_unique<IndexBuffer>(PrimitiveVertex::quadIndex(), PrimitiveVertex::QuadPrimitiveTopology);

            //デフォルトで使用するシェーダーの読み込み
            std::shared_ptr<VertexShader> vs = std::make_shared<VertexShader>(Define::Path::getInstance()->shader() + "NoDelete/Texture2D_VS.cso");
            std::shared_ptr<PixelShader> ps = std::make_shared<PixelShader>(Define::Path::getInstance()->shader() + "NoDelete/Texture2D_PS.cso");
            mEffect = std::make_shared<Effect>(vs, ps);
            mSampler = std::make_unique<Sampler>(TextureAddressMode::Wrap,
                TextureFilterMode::MinMagMipLinear);

            //アルファブレンド・ラスタライザの作成
            mRenderState = std::make_shared<RenderState>(
                std::make_shared<AlphaBlend>(BlendStateDesc::BLEND_DESC(AlphaBlendType::Alignment)),
                std::make_shared<RasterizerState>(RasterizerStateDesc::getDefaultDesc(FillMode::Solid, CullMode::None)));
        }

        //デストラクタ
        SpriteRenderer::~SpriteRenderer() { }

        //2Dスプライトを描画する
        void SpriteRenderer::draw(Sprite2D* sprite) {
            //エフェクトが指定されなかったときはデフォルトのエフェクトを使用する
            draw(sprite, mEffect);
        }

        //2Dスプライトを描画する
        void SpriteRenderer::draw(Sprite2D* sprite, std::shared_ptr<Effect> effect) {
            //コンスタントバッファの取得
            ConstantBufferManager* cmanager = Utility::getConstantBufferManager();

            effect->set();

            //テクスチャデータ
            sprite->getTexture()->setData(ShaderInputType::Pixel, 0);
            mSampler->setData(ShaderInputType::Pixel, 0);

            //モデル・プロジェクション行列の設定
            cmanager->setMatrix(ConstantBufferParameterType::World2D, sprite->getModelMatrix());

            //UV情報の設定
            Math::Rect rect = sprite->getSrcRect();
            cmanager->setFloat(ConstantBufferParameterType::UVLeft, rect.getXMin());
            cmanager->setFloat(ConstantBufferParameterType::UVTop, rect.getYMin());
            cmanager->setFloat(ConstantBufferParameterType::UVWidth, rect.getWidth());
            cmanager->setFloat(ConstantBufferParameterType::UVHeight, rect.getHeight());

            //色の設定
            cmanager->setColor(ConstantBufferParameterType::Color, sprite->getColor());

            cmanager->send();

            mRenderState->setPipeline();

            //描画
            mVertexBuffer->setData();
            mIndexBuffer->setData();
            mIndexBuffer->drawCall();
        }

        void SpriteRenderer::draw(Sprite3D* sprite) {
            //コンスタントバッファの取得
            ConstantBufferManager* cmanager = Utility::getConstantBufferManager();

            //エフェクト
            mEffect->set();

            //テクスチャデータ
            sprite->getTexture()->setData(ShaderInputType::Pixel, 0);
            mSampler->setData(ShaderInputType::Pixel, 0);

            auto bill = [](const Math::Vector3& billPos, const Math::Vector3& targetPos, const Math::Vector3& up) {
                Math::Matrix4x4 mat = Math::Matrix4x4::createView({ targetPos,billPos,up });
                mat = Math::Matrix4x4::inverse(mat);
                mat.m[3][0] = 0;
                mat.m[3][1] = 0;
                mat.m[3][2] = 0;
                return mat;
            };

            Math::Matrix4x4 billboardRotation = bill(
                sprite->getPosition(),
                Utility::getCameraManager()->getPerspectiveCamera()->getPosition(),
                Utility::getCameraManager()->getPerspectiveCamera()->getUpVector());
            Math::Matrix4x4 world = billboardRotation;
            world.m[3][0] = sprite->getPosition().x;
            world.m[3][1] = sprite->getPosition().y;
            world.m[3][2] = sprite->getPosition().z;
            cmanager->setMatrix(ConstantBufferParameterType::World3D, world);

            //UV情報の設定
            Math::Rect rect = sprite->getSrcRect();
            cmanager->setFloat(ConstantBufferParameterType::UVLeft, rect.getXMin());
            cmanager->setFloat(ConstantBufferParameterType::UVTop, rect.getYMin());
            cmanager->setFloat(ConstantBufferParameterType::UVWidth, rect.getWidth());
            cmanager->setFloat(ConstantBufferParameterType::UVHeight, rect.getHeight());

            //色の設定
            cmanager->setColor(ConstantBufferParameterType::Color, sprite->getColor());

            cmanager->send();

            //描画
            mVertexBuffer->setData();
            mIndexBuffer->setData();
            mIndexBuffer->drawCall();
        }

    } //Graphics 
} //Framework 
