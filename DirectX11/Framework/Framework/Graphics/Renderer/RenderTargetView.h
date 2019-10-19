#pragma once
#include "Framework/Graphics/Color4.h"
#include "Framework/Graphics/Resource/Texture2D.h"
#include "Framework/Utility/Property.h"
#include "Framework/Graphics/Renderer/Viewport.h"

namespace Framework {
    namespace Graphics {
        /**
        * @class RenderTargetView
        * @brief レンダーターゲットビュー
        */
        class RenderTargetView {
        public:
            /**
            * @brief コンストラクタ
            * @param texture リソーステクスチャ
            * @param desc レンダーターゲットビューの設定
            * @param backColor 背景色
            */
            RenderTargetView(ID3D11Device* device, std::shared_ptr<Texture2D> texture, const D3D11_RENDER_TARGET_VIEW_DESC* desc, const Viewport& viewport, const Color4& backColor);
            /**
            * @brief コンストラクタ
            * @param texture リソーステクスチャ
            * @param desc レンダーターゲットビューの設定
            * @param depthStencilTexture 深度・ステンシルビューテクスチャ
            * @param dsvDesc 深度・ステンシルビューの設定
            * @param backColor 背景色
            */
            RenderTargetView(ID3D11Device* device, std::shared_ptr<Texture2D> texture, const D3D11_RENDER_TARGET_VIEW_DESC* desc,
                std::shared_ptr<Texture2D> depthStencilTexture, const D3D11_DEPTH_STENCIL_VIEW_DESC* dsvDesc, const Viewport& viewport, const Color4& backColor);
            /**
            * @brief デストラクタ
            */
            ~RenderTargetView();
            /**
            * @brief レンダーターゲットビューを取得する
            */
            ComPtr<ID3D11RenderTargetView> getRenderTargetView() const;
            /**
            * @brief レンダーターゲットのクリア
            */
            void clear(ID3D11DeviceContext* context);
            /**
            * @brief レンダーターゲットをセットする
            */
            void set(ID3D11DeviceContext* context);
            /**
            * @brief 描画終了
            */
            void end(ID3D11DeviceContext* context);
        private:
            ComPtr<ID3D11RenderTargetView> mRenderTargetView; //!< レンダーターゲットビュー
            ComPtr<ID3D11DepthStencilView> mDepthStencilView; //!< 深度・ステンシルビュー
            Viewport mViewport; //!< ビューポート
        private:
            PROPERTY(Color4, mBackColor, BackColor);
            PROPERTY(bool, mEnableDepthStencil, EnableDepthStencil);
        };

    } //Graphics 
} //Framework 
