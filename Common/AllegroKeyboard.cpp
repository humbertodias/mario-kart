#include "AllegroKeyboard.h"
#include <allegro5/allegro.h>

AllegroKeyboard::AllegroKeyboard() {
  al_install_keyboard();
  queue = al_create_event_queue();
  al_register_event_source(queue, al_get_keyboard_event_source());
}

AllegroKeyboard::~AllegroKeyboard() {
  if (queue) {
    al_destroy_event_queue(queue);
  }
}

void AllegroKeyboard::update() {
  ALLEGRO_EVENT event;
  while (al_get_next_event(queue, &event)) {
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
      keys[event.keyboard.keycode] = true;
    } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
      keys[event.keyboard.keycode] = false;
    }
  }
}

bool AllegroKeyboard::isKeyDown(int keycode) const {
  auto it = keys.find(keycode);
  return it != keys.end() && it->second;
}
