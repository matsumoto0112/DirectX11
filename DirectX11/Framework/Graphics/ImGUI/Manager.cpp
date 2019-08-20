#include "Manager.h"
#include "Utility/Debug.h"
#include "Utility/Wrap/DirectX.h"
#include "Utility/Wrap/OftenUsed.h"
#include "Utility/ImGUI/Window.h"

namespace Framework {
namespace ImGUI {

Manager::Manager() {
#ifdef _DEBUG
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    bool success = ImGui_ImplWin32_Init(Utility::getMainHWND());
    MY_ASSERTION(success, "ImGUIの初期化に失敗しました");
    success = ImGui_ImplDX11_Init(Utility::getDevice(), Utility::getContext());
    MY_ASSERTION(success, "ImGUIの初期化に失敗しました");
#endif // DEBUG
}

Manager::~Manager() {
    ImGui_ImplDX11_Shutdown();
    ImGui::DestroyContext();
}

void Manager::drawAll() {
    for (auto&& window : mWindows) {
        window->draw();
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void Manager::add(Window* window) {
    mWindows.emplace_back(window);
}

} //ImGUI 
} //Framework 
