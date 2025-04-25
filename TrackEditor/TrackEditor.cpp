#include "TrackEditor.h"
#include "AllegroScreen.h"
#include "AllegroSystem.h"
#include "Camera.h"
#include "SuperMode7.h"
#include "Track.h"

#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

using namespace std;

TrackEditor::TrackEditor() : mQuit(false) {
  mCurrentTrack = new Track(1);
  mCamera = new Camera();
}

TrackEditor::~TrackEditor() {}

void TrackEditor::processInputEvents() {
  ALLEGRO_KEYBOARD_STATE keyState;
  al_get_keyboard_state(&keyState);

  if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
    mQuit = true;

  if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
    mCamera->setY(mCamera->y() + sin(mCamera->angle()) * 2);
    mCamera->setX(mCamera->x() + cos(mCamera->angle()) * 2);
  }
  if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
    mCamera->setY(mCamera->y() - sin(mCamera->angle()) * 2);
    mCamera->setX(mCamera->x() - cos(mCamera->angle()) * 2);
  }

  if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
    mCamera->setAngle(mCamera->angle() - 0.1);

  if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
    mCamera->setAngle(mCamera->angle() + 0.1);
}

void TrackEditor::update() {}

void TrackEditor::render() {
  ALLEGRO_BITMAP *buffer = AllegroSystem::Instance()->screen()->bitmap();

  // Render the track
  SuperMode7::DrawMode7Stretched(
      buffer, mCurrentTrack->bitmap(), mCamera->angle(), mCamera->x(),
      mCamera->y(), mCamera->mode7Params(), al_map_rgb(175, 230, 245));

  // Debug information
  ALLEGRO_FONT *font = al_load_font("Data/Arial.ttf", 12, 0); // Make sure the font is loaded
  if (font) {
    al_draw_textf(font, al_map_rgb(0, 0, 255), 10, 10, 0, "Camera X     = %f", mCamera->x());
    al_draw_textf(font, al_map_rgb(0, 0, 255), 10, 20, 0, "Camera Y     = %f", mCamera->y());
    al_draw_textf(font, al_map_rgb(0, 0, 255), 10, 30, 0, "Camera Angle = %f", mCamera->angle());
  }

  // Draw everything to the screen
  al_draw_bitmap(buffer, 0, 0, 0);

  // Flip the display to show everything
  al_flip_display();
}
