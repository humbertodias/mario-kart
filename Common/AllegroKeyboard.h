#ifndef ALLEGRO_KEYBOARD_H
#define ALLEGRO_KEYBOARD_H

#include <allegro5/allegro.h>
#include <unordered_map>

class AllegroKeyboard {
public:
  AllegroKeyboard();
  ~AllegroKeyboard();

  void update();
  bool isKeyDown(int keycode) const;

private:
  ALLEGRO_EVENT_QUEUE* queue = nullptr;
  std::unordered_map<int, bool> keys;
};

#endif
