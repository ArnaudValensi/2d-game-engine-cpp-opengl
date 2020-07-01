#pragma once

#include "m.h"
#include <SDL_events.h>
#include <glm/fwd.hpp>
#include <unordered_set>

class Events {
private:
  SDL_Event m_Event;
  bool m_QuitEvent;
  bool m_WindowResizeEvent;
  glm::ivec2 m_WindowSize;
  std::unordered_set<SDL_Keycode> m_KeysDown;
  std::unordered_set<SDL_Keycode> m_KeysDownThisTick;
  std::unordered_set<SDL_Keycode> m_KeysUpThisTick;
  int m_VerticalMouseScroll;

  void SetKeyDown(SDL_Keycode keycode);
  void SetKeyUp(SDL_Keycode keycode);

public:
  void Update();
  [[nodiscard]] bool HasQuitEvent() const;
  [[nodiscard]] bool GetKeyDownThisTick(SDL_Keycode keycode) const;
  [[nodiscard]] bool GetKeyUpThisTick(SDL_Keycode keycode) const;
  [[nodiscard]] bool GetKeyDown(SDL_Keycode keycode) const;
  [[nodiscard]] bool IsWindowResizedThisTick() const;
  [[nodiscard]] glm::ivec2 GetNewWindowSize() const;
  [[nodiscard]] int GetVerticalMouseScroll() const;
};
