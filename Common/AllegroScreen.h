#ifndef ALLEGRO_SCREEN_H
#define ALLEGRO_SCREEN_H

#include "ObjectSize.h"  // You should define this
#include "ColorDepth.h"  // Enum like: DepthAuto, 16, 24, 32...
#include <allegro5/allegro.h>

class AllegroScreen {
public:
  AllegroScreen(const ObjectSize &size, bool fullScreen, ColorDepth colorDepth);
  inline ALLEGRO_BITMAP *bitmap() const { return mBitmap; }

private:
  ALLEGRO_DISPLAY *mDisplay = nullptr;
  ALLEGRO_BITMAP *mBitmap = nullptr;
};

#endif
