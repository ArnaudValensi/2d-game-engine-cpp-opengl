#pragma once


#include <functional>

class Lifecycle {
private:
    std::function<void(double)> m_OnUpdate;
    std::function<void()> m_OnRender;
    bool m_Quit = false;

public:
    void OnUpdate(std::function<void(double)> function);
    void OnRender(std::function<void()> on_render);
    void Start();
    void Stop();
};


