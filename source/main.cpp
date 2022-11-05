// A program that has a DVD logo that moves around the screen

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <wiiuse/wpad.h>

#include <grrlib.h>

#include "dvdlogo_png.h"

// Background color
#define GRRLIB_BLACK 0x000000FF

// DVD Logo color palette
#define GRRLIB_WHITE 0xFFFFFFFF
#define GRRLIB_RED 0xFF0000FF
#define GRRLIB_PASTELPINK 0xDEA5A4FF
#define GRRLIB_PASTELPURPLE 0x9F99C2FF
#define GRRLIB_PASTELGREEN 0x41A56BFF
#define GRRLIB_PASTELYELLOW 0xF2E8B4FF
#define GRRLIB_LAVENDER 0x8C3C8EFF

// Screen size
#define SCREEN_MAX_X 490
#define SCREEN_MAX_Y 390

// Random number generator
int random(int min, int max)
{
    time_t t;
    srand((unsigned) time(&t));
    return (rand() % (max - min + 1)) + min;
}

// DVD Logo colors
unsigned int dvdColors[] = {GRRLIB_WHITE, GRRLIB_RED, GRRLIB_PASTELPINK, GRRLIB_PASTELPURPLE, GRRLIB_PASTELGREEN, GRRLIB_PASTELYELLOW, GRRLIB_LAVENDER};

int main()
{
    // Input
    u32 wpaddown;

    // Get the DVD logo image and store it in a GRRLIB_texImg variable, with proper dimensions.
    GRRLIB_texImg *tex_dvdlogo = GRRLIB_LoadTexture(dvdlogo_png);

    // Set up the DVD logo velocity
    float dvd_vx = 1;
    float dvd_vy = 1;

    // Set up the DVD logo's initial position
    float dvd_x = SCREEN_MAX_X / 2;
    float dvd_y = SCREEN_MAX_Y / 2;

    // Initialize the graphics system
    GRRLIB_Init();
    WPAD_Init();

    // Randomly generate the DVD logo's initial velocity
    int x_rand = random(0, 1);
    int y_rand = random(0, 1);

    // Initialize DVD color to white
    unsigned int dvd_color = dvdColors[0];

    // Main loop
    while (1)
    {
        // Get the current state of the controller
        WPAD_ScanPads();
        wpaddown = WPAD_ButtonsDown(0);

        // Exit if the home button is pressed
        if (wpaddown & WPAD_BUTTON_HOME)
        {
            break;
        }

        // FIll screen background with black
        GRRLIB_FillScreen(GRRLIB_BLACK);

        // Draw the DVD logo
        GRRLIB_DrawImg(dvd_x, dvd_y, tex_dvdlogo, 0, 1, 1, dvd_color);

        // Start moving the DVD logo, depending on the random velocity
        if (x_rand == 0)
            dvd_x += dvd_vx;
        else
            dvd_x -= dvd_vx;

        if (y_rand == 0)
            dvd_y += dvd_vy;
        else
            dvd_y -= dvd_vy;

        // DVD logo bounce and color change
        if (dvd_x > SCREEN_MAX_X || dvd_x < 0)
        {
            dvd_vx = -dvd_vx;
            dvd_color = dvdColors[random(0, 6)];
        }
        if (dvd_y > SCREEN_MAX_Y || dvd_y < 0)
        {
            dvd_vy = -dvd_vy;
            dvd_color = dvdColors[random(0, 6)];
        }

        // Render the frame
        GRRLIB_Render();
    }

    // Clean up the graphics system and exit
    GRRLIB_FreeTexture(tex_dvdlogo);
    GRRLIB_Exit();

    return 0;
}