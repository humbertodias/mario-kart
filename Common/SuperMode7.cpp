#include "SuperMode7.h"
#include <cmath>
#include <iostream>
#include <allegro5/allegro.h>
#include "Config.h"

namespace SuperMode7 {

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <cmath>

    // Very, very slow ;p
    void DrawMode7Stretched(ALLEGRO_BITMAP *target, ALLEGRO_BITMAP *bitmap, float angle,
                            float cameraX, float cameraY, Params params,
                            ALLEGRO_COLOR backgroundColor) {
        // TODO
        // int screenX, screenY;
        //
        // float distance, horizontalScale;
        //
        // int temp1 = al_get_bitmap_width(bitmap) - 1;
        // int temp2 = al_get_bitmap_height(bitmap) - 1;
        //
        // float lineDX, lineDY;
        // float spaceX, spaceY;
        //
        // static ALLEGRO_BITMAP *temp = nullptr;
        // if (!temp) {
        //     temp = al_create_bitmap(SCREEN_W / 2, SCREEN_H / 2);
        // }
        //
        // al_set_target_bitmap(temp);
        // al_clear_to_color(backgroundColor);
        //
        // for (screenY = -params.horizon; screenY < al_get_bitmap_height(temp); screenY++) {
        //     distance = (params.spaceZ * params.scaleY) / (screenY + params.horizon);
        //     horizontalScale = (distance / params.scaleX);
        //     lineDX = -sin(angle) * horizontalScale;
        //     lineDY = cos(angle) * horizontalScale;
        //     spaceX = cameraX + (distance * cos(angle)) - al_get_bitmap_width(temp) * lineDX;
        //     spaceY = cameraY + (distance * sin(angle)) - al_get_bitmap_width(temp) * lineDY;
        //
        //     for (screenX = 0; screenX < al_get_bitmap_width(temp); screenX++) {
        //         if ((spaceX < temp1) && (spaceY < temp2) && (spaceX > 0) && (spaceY > 0)) {
        //             ALLEGRO_COLOR pixelColor = al_get_pixel(bitmap, spaceX, spaceY);
        //             al_put_pixel(screenX, screenY, pixelColor);
        //         }
        //
        //         spaceX += lineDX + lineDX;
        //         spaceY += lineDY + lineDY;
        //     }
        // }
        //
        // al_set_target_bitmap(target);
        // al_draw_scaled_bitmap(temp, 0, 0, al_get_bitmap_width(temp), al_get_bitmap_height(temp),
        //                       0, 0, SCREEN_W, SCREEN_H, 0);
        //
        // al_destroy_bitmap(temp);
    }


void DrawObject(ALLEGRO_BITMAP *target, ALLEGRO_BITMAP *bitmap, float angle, float objectX,
                float objectY, float cameraX, float cameraY, Params params) {
    float newObjectX = objectX - cameraX;
    float newObjectY = objectY - cameraY;

    float spaceX = (newObjectX * cos(angle)) + (newObjectY * sin(angle));
    float spaceY = (-(newObjectX * sin(angle))) + (newObjectY * cos(angle));

    int screenX = al_get_bitmap_width(target) / 2 + ((params.scaleX / spaceX) * spaceY);
    int screenY = ((params.spaceZ * params.scaleY) / spaceX) - params.horizon;

    screenY *= 2;

    int width = al_get_bitmap_width(bitmap) * (params.objScaleX / spaceX);
    int height = al_get_bitmap_height(bitmap) * (params.objScaleY / spaceX);

    al_draw_scaled_bitmap(bitmap, 0, 0, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),
                          screenX - width / 2, screenY - height, width, height, 0);
}

}; // namespace SuperMode7
