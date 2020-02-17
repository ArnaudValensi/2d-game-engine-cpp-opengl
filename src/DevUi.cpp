//
// Created by Arnaud Valensi on 14/02/2020.
//

#include <imgui.h>
#include "DevUi.h"
#include "Events.h"

bool s_ShowMainMenu = false;
bool s_ShowDemoWindow = false;

static void ShowMainMenu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Window")) {
            if (ImGui::MenuItem("DearImGui Demo")) { s_ShowDemoWindow = !s_ShowDemoWindow; }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void DevUi::Draw() {
    if (s_ShowMainMenu) { ShowMainMenu(); }
    if (s_ShowDemoWindow) { ImGui::ShowDemoWindow(&s_ShowDemoWindow); }
}

void DevUi::Update(const Events& events) {
   if (events.GetKeyDownThisTick(SDLK_F1)) {
       s_ShowMainMenu = !s_ShowMainMenu;
   }
}
