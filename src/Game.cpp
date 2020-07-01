#include "Game.h"
#include "DevUi.h"
#include "Events.h"
#include "Lifecycle.h"
#include "Map.h"
#include "Player.h"
#include "Renderer.h"
#include "Resources.h"
#include "SpriteBatch.h"

int Game::Run() {
  Renderer renderer;
  Resources resources;
  Events events;
  Lifecycle lifecycle;
  DevUi dev_ui;

  renderer.Init();
  resources.Create();

  Map map;
  map.Init(resources, "./assets/maps/level1.txt");

  Sprite player_sprite = resources.GetSprite(Resources::Sprites::Player);
  Player player(player_sprite, &events);
  Camera camera(events, renderer);
  SpriteBatch sprite_batch;
  sprite_batch.Init(camera);

  lifecycle.OnUpdate([&](double delta_time) {
    events.Update();

    if (events.HasQuitEvent() || events.GetKeyDownThisTick(SDLK_ESCAPE)) {
      lifecycle.Stop();
    }

    renderer.Update(events);
    player.Update(delta_time);
    camera.Update(delta_time);
    dev_ui.Update(events);
  });

  lifecycle.OnRender([&]() {
    renderer.BeforeRender();
    map.Draw(sprite_batch);
    player.Draw(sprite_batch);
    dev_ui.Draw();
    renderer.Render();
  });

  lifecycle.Start();

  renderer.Shutdown();

  return 0;
}
