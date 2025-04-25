#ifndef _OPPONENT_H
#define _OPPONENT_H

#include <string>
#include <allegro5/allegro.h>  // Include the Allegro 5 header

class Opponent {
public:
  enum Character { Mario, Luigi, Peach };

private:
  ALLEGRO_BITMAP *mSprite;   // Allegro 5 uses ALLEGRO_BITMAP instead of BITMAP
  ALLEGRO_BITMAP *mBitmap;

  float mPositionX;
  float mPositionY;

  Character mCharacter;

public:
  Opponent(Character character);

  void update();

  inline float x() const { return mPositionX; }
  inline void setX(float positionX) { mPositionX = positionX; }
  inline float y() const { return mPositionY; }
  inline void setY(float positionY) { mPositionY = positionY; }

  inline ALLEGRO_BITMAP *bitmap() const { return mBitmap; }  // Return ALLEGRO_BITMAP*

  void loadBitmap(const std::string &fileName);

  void updateBmp(int step);
};

#endif
