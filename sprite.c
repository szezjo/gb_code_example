#include <gb/gb.h>
#include "face.c"

// this move() function belows only accepts one-row metasprites
void move(int metasprite[], int len, int x_delta, int y_delta, int *px, int *py) {
    *px+=x_delta;
    *py+=y_delta;
    for (int i=0; i<len; i++) {
        move_sprite(metasprite[i], *px+i*8, *py);
    }
    delay(10);
}

void main() {
    // Starting position
    int x = 80;
    int y = 80;
    int *px = &x;
    int *py = &y;
    char A_is_down = 0;

    // Switch sprite type to 8x16
    SPRITES_8x16;
    // Move tiles from 0 (included) to 8 (excluded) from Face to VRAM
    set_sprite_data(0,8,Face);
    // Set tile 0 (and tile 1, because it's 8x16) to sprite 0
    set_sprite_tile(0,0);
    // Move sprite 0 to the starting position
    move_sprite(0,*px,*py);
    // Set tile 2 (and tile 3) to sprite 1
    set_sprite_tile(1,2);
    // Move sprite 1 next to sprite 0 (x+8)
    move_sprite(1,*px+8,*py);
    SHOW_SPRITES;

    int metasprite[2] = {0, 1};

    while(1) {
        // & is used instead of ==, so multiple directions can be pressed at once allowing diagonal movement
        if(joypad() & J_RIGHT) move(metasprite, 2, 1, 0, px, py);
        if(joypad() & J_LEFT) move(metasprite, 2, -1, 0, px, py);
        if(joypad() & J_DOWN) move(metasprite, 2, 0, 1, px, py);
        if(joypad() & J_UP) move(metasprite, 2, 0, -1, px, py);
        // Check if the state of A button is changed - if true, change the sprite
        if(!A_is_down) {
            if(joypad() & J_A) {
                set_sprite_tile(0,4);
                set_sprite_tile(1,6);
                A_is_down = 1;
            }
        }
        else {
            if(!(joypad() & J_A)) {
                set_sprite_tile(0,0);
                set_sprite_tile(1,2);
                A_is_down = 0;
            } 
        }
    }
}