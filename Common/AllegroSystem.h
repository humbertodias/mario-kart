#ifndef ALLEGRO_SYSTEM_H
#define ALLEGRO_SYSTEM_H

#include "ObjectSize.h"
#include "ColorDepth.h"

class AllegroScreen;
class AllegroKeyboard;

#include <allegro5/allegro.h>

class AllegroSystem {
public:
  static AllegroSystem* Instance();
  ~AllegroSystem();

  bool setupScreen(const ObjectSize& size, bool fullScreen, ColorDepth colorDepth);
  AllegroKeyboard* installKeyboard();
  void initializeTimers();
  void pollEvents();
  void waitForTicks();

  inline AllegroScreen *screen() const { return mScreen; }

  static volatile long SpeedCounter;
  static volatile long TimeTicks;
  static volatile int Fps;
  static volatile int AvgFps;
  static volatile int LastFps;

private:
  AllegroSystem();
  static AllegroSystem* mInstance;

  AllegroScreen* mScreen = nullptr;
  AllegroKeyboard* mKeyboard = nullptr;

  ALLEGRO_EVENT_QUEUE* eventQueue = nullptr;
  ALLEGRO_TIMER* timer = nullptr;
  double lastTime;
};

#endif
