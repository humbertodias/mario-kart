#include "AllegroKeyboard.h"
#include "AllegroSystem.h"
#include "TrackEditor.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <iostream>
#include <allegro5/allegro_ttf.h>

int main() {
  // Initialize Allegro 5
  if (!al_init()) {
    std::cerr << "Failed to initialize Allegro 5!" << std::endl;
    return -1;
  }

  // Initialize the necessary Allegro 5 addons
  if (!al_init_primitives_addon() || !al_init_font_addon() || !al_init_ttf_addon()) {
    std::cerr << "Failed to initialize Allegro 5 addons!" << std::endl;
    return -1;
  }

  if (!al_install_keyboard()) {
    std::cerr << "Failed to install keyboard!" << std::endl;
    return -1;
  }

  // Setup screen and timer
  AllegroSystem *allegro = AllegroSystem::Instance();
  allegro->setupScreen(ObjectSize(640, 480), false, DepthAuto);
  allegro->initializeTimers();

  TrackEditor editor;

  // Create a timer for controlling game speed
  ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0); // 60 FPS timer
  if (!timer) {
    std::cerr << "Failed to create timer!" << std::endl;
    return -1;
  }

  // Create an event queue
  ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
  if (!event_queue) {
    std::cerr << "Failed to create event queue!" << std::endl;
    al_destroy_timer(timer);
    return -1;
  }

  // Register events with the event queue
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  // al_register_event_source(event_queue, al_get_display_event_source(allegro->getDisplay()));

  // Start the timer
  al_start_timer(timer);

  while (!editor.quit()) {
    ALLEGRO_EVENT ev;
    while (al_get_next_event(event_queue, &ev)) {
      if (ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_KEY_UP) {
        editor.processInputEvents();
      }

      if (ev.type == ALLEGRO_EVENT_TIMER) {
        editor.update();
      }

      // Handle display resize or other display events
      if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
        // al_acknowledge_resize(allegro->getDisplay());
      }
    }

    // Render
    editor.render();

    // Sync to the correct FPS rate
    al_rest(0.001);
  }

  // Clean up resources
  al_destroy_timer(timer);
  al_destroy_event_queue(event_queue);

  return 0;
}
