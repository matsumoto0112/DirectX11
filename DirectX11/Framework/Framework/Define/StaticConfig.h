#pragma once

namespace Framework {
    namespace Define {
        /**
        * @class StaticConfig
        * @brief 定数的な設定
        * @TODO: 余裕のある時に外部ファイルに移したい
        */
        class StaticConfig {
        public:
            static constexpr UINT MSAA_COUNT = 1; //!< MSAAのカウント
        };

    } //Define 
} //Framework 