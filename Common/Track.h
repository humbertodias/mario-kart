#ifndef _TRACK_H
#define _TRACK_H

#include <allegro5/allegro.h>

struct TrackInfo {
  double startCameraX;
  double startCameraY;
  double startAngle;
};

class Track {
private:
  int mNumber;
  ALLEGRO_BITMAP *mBitmap;

public:
  Track(int number);

  const TrackInfo info();

  inline ALLEGRO_BITMAP *bitmap() const { return mBitmap; }
};

#endif
