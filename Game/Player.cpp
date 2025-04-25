#include "Player.h"

#include <cmath>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> // Add-on for image loading

Player::Player() {
    // Create an empty bitmap for the player sprite
    mBitmap = al_create_bitmap(32, 32);
    mSprite = al_load_bitmap("Data/Mario.bmp");

    if (!mSprite) {
        std::cerr << "Failed to load player sprite!" << std::endl;
    }

    // Optional: You can clear the bitmap and draw an initial background
    al_set_target_bitmap(mBitmap);
    al_clear_to_color(al_map_rgb(0, 0, 0)); // Clear the bitmap with black
    al_draw_bitmap(mSprite, 0, 0, 0); // Draw the sprite into the bitmap

    // Set initial positions and velocities
    mPositionX = 913;
    mPositionY = 652;

    mAcc = 0;
    mAngle = -1.57;
    mAngleAcc = -1.57;
    mVectorLength = 0;
}

void Player::processInputEvents(ALLEGRO_KEYBOARD_STATE * keyboardState) {
    // Adjust acceleration and angle based on input
    if (al_key_down(keyboardState, ALLEGRO_KEY_UP))
        mAcc += 0.03;
    else
        mAcc -= 0.03;

    if (al_key_down(keyboardState, ALLEGRO_KEY_DOWN))
        mAcc -= 0.2;
    else if (al_key_down(keyboardState, ALLEGRO_KEY_LEFT))
        mAngleAcc -= (6 - mAcc) / 100;

    if (al_key_down(keyboardState, ALLEGRO_KEY_RIGHT))
        mAngleAcc += (6 - mAcc) / 100;
}

void Player::update() {
    // Clamp acceleration between 0 and 4
    if (mAcc > 4.0)
        mAcc = 4.0;
    if (mAcc < 0)
        mAcc = 0;

    // Calculate new position based on velocity and angle
    mPositionX += mAcc * cos(mAngle);
    mPositionY += mAcc * sin(mAngle);

    // Update angle with some wrapping to keep it within 0 to 2π
    float delta = mAngle - mAngleAcc;
    if (mAngle < -M_PI * 2) {
        mAngle = delta * -1;
        mAngleAcc = delta * -1;
    } else if (mAngle > M_PI * 2) {
        mAngle = delta * -1;
        mAngleAcc = delta * -1;
    } else {
        mAngle = mAngleAcc;
    }
}

void Player::updateBmp(int step) {
    // Update the player's bitmap based on the step
    al_draw_bitmap(mSprite, mPositionX, mPositionY, 0);
}
