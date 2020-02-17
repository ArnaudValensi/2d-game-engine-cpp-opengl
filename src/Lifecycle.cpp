#include <SDL_timer.h>
#include "Lifecycle.h"

void Lifecycle::OnUpdate(std::function<void(double)> on_update) {
    m_OnUpdate = on_update;
}

void Lifecycle::OnRender(std::function<void()> on_render) {
    m_OnRender = on_render;
}

void Lifecycle::Start() {
    const double update_rate = 1000.0 / 120.0;
    const double render_rate = 1000.0 / 60.0;
    double current_time = SDL_GetTicks();
    double update_accumulator = 0.0;
    double render_accumulator = 0.0;

    while (!m_Quit) {
        double new_time = SDL_GetTicks();
        double frame_time = new_time - current_time;
        current_time = new_time;

        update_accumulator += frame_time;
        render_accumulator += frame_time;

        bool isReadyToUpdate = update_accumulator >= update_rate;
        bool isReadyToRender = render_accumulator >= render_rate;

        // Sleep if nothing to do.
        if (!isReadyToUpdate && !isReadyToRender) {
            double next_update = update_rate - update_accumulator;
            double next_render = render_rate - render_accumulator;
            double next_event_time = fmin(next_update, next_render);

            // The delay granularity is at least 10 ms according to SDL doc.
            if (next_event_time > 10.0) {
                SDL_Delay(next_event_time);
            }

            continue;
        }

        // Update.
        // We want the update to always increase by update_rate steps
        // and simulate multiple updates if it is late.
        while (update_accumulator >= update_rate) {
            m_OnUpdate(update_rate / 1000.0);

            update_accumulator -= update_rate;
        }

        // Rendering.
        if (isReadyToRender) {
            m_OnRender();

            render_accumulator -= render_rate;

            // If the rendering is late, we don't want to keep up in case
            // the accumulator was more than twice the render_rate.
            render_accumulator = fmod(render_accumulator, render_rate);
        }
    }
}

void Lifecycle::Stop() {
    m_Quit = true;
}
