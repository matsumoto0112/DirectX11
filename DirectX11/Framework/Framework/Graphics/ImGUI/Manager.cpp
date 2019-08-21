#include "Manager.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/Wrap/DirectX.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/ImGUI/Window.h"

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
    MY_ASSERTION(success, "ImGUI‚Ì‰Šú‰»‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
    success = ImGui_ImplDX11_Init(Utility::getDevice(), Utility::getContext());
    MY_ASSERTION(success, "ImGUI‚Ì‰Šú‰»‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
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
