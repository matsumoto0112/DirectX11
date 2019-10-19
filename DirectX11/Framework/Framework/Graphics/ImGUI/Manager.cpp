#include "Manager.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/ImGUI/Window.h"

namespace Framework {
namespace ImGUI {

Manager::Manager() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    bool success = ImGui_ImplWin32_Init(Utility::getMainHWND());
    MY_ASSERTION(success, "ImGUI�̏������Ɏ��s���܂���");
    success = ImGui_ImplDX11_Init(
        Graphics::DX11InterfaceAccessor::getDevice().Get(),
        Graphics::DX11InterfaceAccessor::getContext().Get());
    MY_ASSERTION(success, "ImGUI�̏������Ɏ��s���܂���");
}

Manager::~Manager() {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void Manager::beginFrame() {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void Manager::drawAll() {
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

} //ImGUI 
} //Framework 
