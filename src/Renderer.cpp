#include "Renderer.h"
#include "Config.h"
#include "Rect.h"
#include "Shader.h"
#include "debug.h"
#include <GL/gl3w.h>
#include <SDL.h>
#include <fmt/core.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>

void Renderer::Init() {
  // NOTE: There is two error with SDL:
  // "MessageTracer: Falling back to default whitelist": don't know why.
  // "CGContextSetFillColorWithColor: invalid context 0x0.":
  // https://bugzilla.libsdl.org/show_bug.cgi?id=4470
  // https://hg.libsdl.org/SDL/rev/065b94926987
  // Should be fixed on a version later 2.0.10.
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    PANIC("SDL_Init failed: %s\n", SDL_GetError());
  }

  SDL_version compiled;
  SDL_version linked;

  SDL_VERSION(&compiled);
  SDL_GetVersion(&linked);

  fmt::print("SDL2 linked version: {}.{}.{}, compiled version: {}.{}.{}\n", compiled.major,
             compiled.minor, compiled.patch, linked.major, linked.minor, linked.patch);

  // Decide GL+GLSL versions
#if __APPLE__
  // GL 3.2 Core + GLSL 150
  const char* glsl_version = "#version 150";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
  // GL 3.0 + GLSL 130
  const char* glsl_version = "#version 130";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

  // Create window with graphics context
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  m_ScreenScale = 1;

  SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL
                                                   | SDL_WINDOW_RESIZABLE
                                                   | SDL_WINDOW_ALLOW_HIGHDPI);
  m_Window = SDL_CreateWindow("Game",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              REFERENCE_SCREEN_WIDTH,
                              REFERENCE_SCREEN_HEIGHT,
                              window_flags);

  if (!m_Window) {
    PANIC("SDL_CreateWindow failed: %s\n", SDL_GetError());
  }

  // This seems to create the following message on debug:
  // "MessageTracer: Falling back to default whitelist".
  SDL_GLContext m_GlContext = SDL_GL_CreateContext(m_Window);
  if (!m_GlContext) {
    PANIC("SDL_GL_CreateContext failed: %s\n", SDL_GetError());
  }
  SDL_GL_MakeCurrent(m_Window, m_GlContext);
  SDL_GL_SetSwapInterval(1); // Enable vsync

  if (gl3wInit()) {
    PANIC("Failed to initialize OpenGL loader!\n");
  }

  printf(
    "OpenGL %s, GLSL %s\n",
    glGetString(GL_VERSION),
    glGetString(GL_SHADING_LANGUAGE_VERSION));

  HandleScreenSizeChange();

  GL(glEnable(GL_CULL_FACE));
  GL(glFrontFace(GL_CW));
  GL(glEnable(GL_DEPTH_TEST));
  GL(glEnable(GL_BLEND));
  GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  m_ImGuiIo = &ImGui::GetIO();

  m_ImGuiIo->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
  m_ImGuiIo->ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
  m_ImGuiIo->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
  //io.ConfigViewportsNoAutoMerge = true;
  //io.ConfigViewportsNoTaskBarIcon = true;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();

  // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
  ImGuiStyle& style = ImGui::GetStyle();
  if (m_ImGuiIo->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  // Setup Platform/Renderer bindings
  ImGui_ImplSDL2_InitForOpenGL(m_Window, m_GlContext);
  ImGui_ImplOpenGL3_Init(glsl_version);
}

void Renderer::Shutdown() {
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_GL_DeleteContext(m_GlContext);
  SDL_DestroyRenderer(m_Renderer);
  SDL_DestroyWindow(m_Window);
  SDL_Quit();
}

void Renderer::BeforeRender() {
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(m_Window);
  ImGui::NewFrame();

  GL(glClearColor(1.0f, 1.0f, 0.0f, 1.0f));
  GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Render() {
  // Rendering
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  // Update and Render additional Platform Windows
  // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
  // For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
  if (m_ImGuiIo->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
    SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
  }

  SDL_GL_SwapWindow(m_Window);
}

void Renderer::HandleScreenSizeChange() {
  SDL_GetWindowSize(m_Window, &m_ScreenSize.x, &m_ScreenSize.y);

  int display_w, display_h;
  SDL_GL_GetDrawableSize(m_Window, &display_w, &display_h);

  m_HdpiFactor = display_w / m_ScreenSize.x;

  GL(glViewport(0, 0, display_w, display_h));

  fmt::print(
    "screen size: ({},{}), frame buffer size: ({},{}) hdpi factor: {}\n",
    m_ScreenSize.x, m_ScreenSize.y, display_w, display_h, m_HdpiFactor);

  for (const auto& on_change_screen_size_callback : m_OnScreenChangeEvents) {
    on_change_screen_size_callback();
  }
}

void Renderer::Update(const Events& events) {
  if (events.IsWindowResizedThisTick()) {
    HandleScreenSizeChange();
  }
}

glm::ivec2 Renderer::GetScreenSize() const {
  return m_ScreenSize;
}

void Renderer::OnScreenSizeChange(const std::function<void()>& on_scree_change_event) {
  m_OnScreenChangeEvents.emplace_back(on_scree_change_event);
}
