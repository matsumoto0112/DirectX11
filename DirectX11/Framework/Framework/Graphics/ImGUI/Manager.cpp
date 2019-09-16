#include "Manager.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/Wrap/DirectX.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/ImGUI/Window.h"

namespace Framework {
namespace ImGUI {

Manager::Manager() {
//#ifdef _DEBUG
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    bool success = ImGui_ImplWin32_Init(Utility::getMainHWND());
    MY_ASSERTION(success, "ImGUIÇÃèâä˙âªÇ…é∏îsÇµÇ‹ÇµÇΩ");
    success = ImGui_ImplDX11_Init(Utility::getDevice(), Utility::getContext());
    MY_ASSERTION(success, "ImGUIÇÃèâä˙âªÇ…é∏îsÇµÇ‹ÇµÇΩ");
//#endif // DEBUG
}

Manager::~Manager() {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void Manager::drawAll() {
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

} //ImGUI 
} //Framework 
