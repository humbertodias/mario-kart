#ifndef _PLAYER_H
#define _PLAYER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>  // Allegro 5 image add-on for loading bitmaps
#include <string>

class Player {
private:
  std::string mName;

  ALLEGRO_BITMAP *mSprite;
  ALLEGRO_BITMAP *mBitmap;

  float mPositionX;
  float mPositionY;
  float mAcc;
  float mAngle;
  float mAngleAcc;
  float mVectorLength;

public:
  Player();

  void processInputEvents(ALLEGRO_KEYBOARD_STATE * key_state);
  void update();
  void updateBmp(int step);

  inline float x() const { return mPositionX; }
  inline void setX(float x) { mPositionX = x; }

  inline float y() const { return mPositionY; }
  inline void setY(float y) { mPositionY = y; }

  inline float angle() const { return mAngle; }

  inline ALLEGRO_BITMAP *bitmap() const { return mBitmap; }

};

#endif
