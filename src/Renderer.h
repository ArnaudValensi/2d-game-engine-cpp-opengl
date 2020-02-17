#pragma once

#include <SDL.h>
#include <vector>
#include "Sprite.h"
#include <imgui.h>
#include "SpriteRenderer.h"
#include "Events.h"

class Renderer {
private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    glm::ivec2 m_ScreenSize;
    int m_ScreenScale;
    int m_HdpiFactor;
    ImGuiIO* m_ImGuiIo;
    SDL_GLContext m_GlContext;
    SpriteRenderer m_SpriteRenderer;
    std::vector<std::function<void()>> m_OnScreenChangeEvents;

public:
    void Init();
    void Shutdown();
    void Render();
    void Update(const Events& events);
    void HandleScreenSizeChange();
    [[nodiscard]] glm::ivec2 GetScreenSize() const;
    void BeforeRender();
    void OnScreenSizeChange(const std::function<void()>& on_scree_change_event);
};


