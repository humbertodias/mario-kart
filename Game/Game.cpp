#include "Game.h"
#include "AllegroScreen.h"
#include "AllegroSystem.h"
#include "Camera.h"
#include "Opponent.h"
#include "Player.h"
#include "SuperMode7.h"
#include "Track.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

using namespace std;

Game::Game() : mQuit(false) {
    mCurrentTrack = new Track(1);
    mCamera = new Camera();
    mPlayer = new Player();

    mOpponents[0] = new Opponent(Opponent::Luigi);
    mOpponents[0]->setX(913);
    mOpponents[0]->setY(604);

    mOpponents[1] = new Opponent(Opponent::Peach);
    mOpponents[1]->setX(943);
    mOpponents[1]->setY(627);

    if (!al_init_font_addon()) {
        std::cerr << "Failed to initialize Allegro font addon!" << std::endl;
        return ;
    }

    if (!al_init_ttf_addon()) {
        std::cerr << "Failed to initialize Allegro TTF addon!" << std::endl;
        return ;
    }

    // Load the font
    font = al_load_font("Data/Arial.ttf", 18, 0);
    if (!font) {
        std::cerr << "Failed to load any font!" << std::endl;
        return;
    }
}

Game::~Game() {}

void Game::processInputEvents() {
    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);

    if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
        mQuit = true;
    }

    mPlayer->processInputEvents(&keyState);

    // Uncomment if you need to update camera positions
    /*
    if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
        mCamera->setY(mCamera->y() + sin(mCamera->angle()) * 2);
        mCamera->setX(mCamera->x() + cos(mCamera->angle()) * 2);
    }
    if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
        mCamera->setY(mCamera->y() - sin(mCamera->angle()) * 2);
        mCamera->setX(mCamera->x() - cos(mCamera->angle()) * 2);
    }

    if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
        mCamera->setAngle(mCamera->angle() - 0.1);
    }

    if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
        mCamera->setAngle(mCamera->angle() + 0.1);
    }
    */
}

void Game::update() {
    mPlayer->update();
    mCamera->update(mPlayer);
    mPlayer->updateBmp(mCamera->angle());

    for (int i = 0; i < sizeof(mOpponents) / sizeof(*mOpponents); i++) {
        mOpponents[i]->update();
    }
}

void Game::render() {
    ALLEGRO_BITMAP *buffer = AllegroSystem::Instance()->screen()->bitmap();

    // Clear the screen with a light blue color
    al_clear_to_color(al_map_rgb(175, 230, 245));

    // Render the track using Mode 7 effect
    SuperMode7::DrawMode7Stretched(
        buffer, mCurrentTrack->bitmap(), mCamera->angle(), mCamera->x(),
        mCamera->y(), mCamera->mode7Params(), al_map_rgb(175, 230, 245));

    // Debug information (Camera and Player positions, FPS)
    al_draw_textf(font, al_map_rgb(0, 0, 255), 10, 10, ALLEGRO_ALIGN_LEFT, "Camera X     = %f", mCamera->x());
    al_draw_textf(font, al_map_rgb(0, 0, 255), 10, 20, ALLEGRO_ALIGN_LEFT, "Camera Y     = %f", mCamera->y());
    al_draw_textf(font, al_map_rgb(0, 0, 255), 10, 30, ALLEGRO_ALIGN_LEFT, "Player X     = %f", mPlayer->x());
    al_draw_textf(font, al_map_rgb(0, 0, 255), 10, 40, ALLEGRO_ALIGN_LEFT, "Player Y     = %f", mPlayer->y());
    al_draw_textf(font, al_map_rgb(0, 0, 255), 10, 50, ALLEGRO_ALIGN_LEFT, "Camera Angle = %f", mCamera->angle());
    al_draw_textf(font, al_map_rgb(0, 0, 255), 10, 60, ALLEGRO_ALIGN_LEFT, "Player Angle = %f", mPlayer->angle());
    al_draw_textf(font, al_map_rgb(0, 0, 255), 10, 70, ALLEGRO_ALIGN_LEFT, "FPS          = %i", AllegroSystem::LastFps);

    // Render the player using the Mode 7 effect
    SuperMode7::DrawObject(buffer, mPlayer->bitmap(), mCamera->angle(),
                           mPlayer->x(), mPlayer->y(), mCamera->x(), mCamera->y(),
                           mCamera->mode7Params());

    // Render the opponents
    for (int i = 0; i < sizeof(mOpponents) / sizeof(*mOpponents); i++) {
        Opponent *opponent = mOpponents[i];

        // Calculate opponent relative position
        SuperMode7::DrawObject(buffer, opponent->bitmap(), mCamera->angle(),
                               (mPlayer->x() + opponent->x()) - mCamera->x(),
                               (mPlayer->y() + opponent->y()) - mCamera->y(),
                               opponent->x() - (opponent->x() - mPlayer->x()),
                               opponent->y() - (opponent->y() - mPlayer->y()),
                               mCamera->mode7Params());
    }

    // Flip the display to show everything
    al_flip_display();

}
