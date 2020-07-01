#include "Events.h"
#include "m.h"
#include <SDL_events.h>
#include <imgui.h>
#include <imgui_impl_sdl.h>

void Events::Update() {
  // Reset all.
  m_KeysDownThisTick.clear();
  m_KeysUpThisTick.clear();
  m_WindowResizeEvent = false;
  m_VerticalMouseScroll = 0;

  // Retrieve all events.
  while (SDL_PollEvent(&m_Event)) {
    ImGui_ImplSDL2_ProcessEvent(&m_Event);

    if (m_Event.type == SDL_QUIT) {
      m_QuitEvent = true;
    }
    else if (m_Event.type == SDL_KEYDOWN) {
      SetKeyDown(m_Event.key.keysym.sym);
    }
    else if (m_Event.type == SDL_KEYUP) {
      SetKeyUp(m_Event.key.keysym.sym);
    }
    else if (m_Event.type == SDL_WINDOWEVENT) {
      if (m_Event.window.event == SDL_WINDOWEVENT_RESIZED) {
        m_WindowSize = glm::ivec2(m_Event.window.data1, m_Event.window.data2);
        m_WindowResizeEvent = true;
      }
    }
    else if (m_Event.type == SDL_MOUSEWHEEL) {
      m_VerticalMouseScroll = m_Event.wheel.y;
    }
  }
}

void Events::SetKeyDown(SDL_Keycode keycode) {
  m_KeysDown.insert(keycode);
  m_KeysDownThisTick.insert(keycode);
}

void Events::SetKeyUp(SDL_Keycode keycode) {
  m_KeysDown.erase(keycode);
  m_KeysUpThisTick.insert(keycode);
}

bool Events::HasQuitEvent() const {
  return m_QuitEvent;
}

bool Events::GetKeyDownThisTick(SDL_Keycode keycode) const {
  return m_KeysDownThisTick.find(keycode) != m_KeysDownThisTick.end();
}

bool Events::GetKeyUpThisTick(SDL_Keycode keycode) const {
  return m_KeysUpThisTick.find(keycode) != m_KeysUpThisTick.end();
}

bool Events::GetKeyDown(SDL_Keycode keycode) const {
  return m_KeysDown.find(keycode) != m_KeysDown.end();
}

int Events::GetVerticalMouseScroll() const {
  return m_VerticalMouseScroll;
}

bool Events::IsWindowResizedThisTick() const {
  return m_WindowResizeEvent;
}

glm::ivec2 Events::GetNewWindowSize() const {
  return m_WindowSize;
}
