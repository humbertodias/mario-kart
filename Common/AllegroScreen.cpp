#include "AllegroScreen.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdexcept>
#include <string>

AllegroScreen::AllegroScreen(const ObjectSize &size, bool fullScreen, ColorDepth colorDepth) {
  if (!al_init()) {
    throw std::runtime_error("Failed to initialize Allegro");
  }

  if (!al_init_image_addon()) {
    throw std::runtime_error("Failed to initialize Allegro image addon");
  }

  // Set color depth if specified (Allegro 5 uses 32-bit color by default)
  int bpp = colorDepth;
  if (colorDepth == DepthAuto) {
    bpp = 32; // Default fallback
  }
  al_set_new_display_option(ALLEGRO_COLOR_SIZE, bpp, ALLEGRO_SUGGEST);

  // Set display flags (fullscreen or windowed)
  al_set_new_display_flags(fullScreen ? ALLEGRO_FULLSCREEN_WINDOW : ALLEGRO_WINDOWED);

  // Create the display
  mDisplay = al_create_display(size.width(), size.height());
  if (!mDisplay) {
    throw std::runtime_error("Failed to create display");
  }

  // Create an offscreen bitmap (optional, depends on your rendering logic)
  mBitmap = al_create_bitmap(size.width(), size.height());
  if (!mBitmap) {
    throw std::runtime_error("Failed to create auxiliary bitmap");
  }
}