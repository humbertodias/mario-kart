#include "Opponent.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> // Allegro 5 image add-on for loading bitmaps
#include <iostream>

Opponent::Opponent(Character character) : mCharacter(character) {
  mPositionX = 900;
  mPositionY = 520;

  // Allegro 5 does not have create_bitmap, so we just create an empty bitmap
  mBitmap = al_create_bitmap(32, 32);  // Use al_create_bitmap for Allegro 5

  switch (mCharacter) {
    case Luigi:
      mSprite = al_load_bitmap("Data/Luigi.bmp");
      break;
    case Peach:
      mSprite = al_load_bitmap("Data/Peach.bmp");
      break;
    case Mario:
      mSprite = al_load_bitmap("Data/Mario.bmp");
      break;
  }

  if (!mSprite) {
    std::cerr << "Failed to load sprite" << std::endl;
  }

  // Fill the bitmap with a color (using al_set_target_bitmap to set the drawing target)
  al_set_target_bitmap(mBitmap);  // Set the bitmap as the target for drawing
  al_clear_to_color(al_map_rgb(0, 0, 0));  // Fill with black color
  al_draw_bitmap(mSprite, 0, 0, 0);  // Draw the sprite onto the bitmap
  al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));  // Reset to backbuffer
}

void Opponent::update() {
  // Add your update logic here (e.g., for movement or AI)
  // std::cout << "update" << std::endl;
  // mPositionY -= 0.4;
  // mPositionX -= 0.2;
}

void Opponent::loadBitmap(const std::string &fileName) {
  // Load the bitmap in Allegro 5 using al_load_bitmap
  mBitmap = al_load_bitmap(fileName.c_str());
  if (!mBitmap) {
    std::cerr << "Failed to load bitmap: " << fileName << std::endl;
  }
}

void Opponent::updateBmp(int step) {
  // Update the bitmap (for example, animating through frames)
  // Use al_draw_bitmap to update the bitmap with the proper section (frame) of the sprite
  al_draw_bitmap_region(mSprite, step * 32, 0, 32, 32, 0, 0, 0);  // Draw the specific section
}
