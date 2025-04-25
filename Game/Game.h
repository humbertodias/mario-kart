#ifndef _GAME_H
#define _GAME_H
#include <allegro5/allegro_font.h>

class Track;
class Camera;
class Player;
class Opponent;

class Game {
private:
  bool mQuit;

  Track *mCurrentTrack;
  Camera *mCamera;
  Player *mPlayer;

  Opponent *mOpponents[2];
  ALLEGRO_FONT *font;

public:
  Game();
  ~Game();

  void processInputEvents();
  void update();
  void render();

  inline bool quit() const { return mQuit; }
  inline void setQuit(bool quit) { mQuit = quit; }
};

#endif
