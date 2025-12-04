/**
* Docs: http://wiki.libsdl.org/FrontPage
 * Tutorial: http://lazyfoo.net/tutorials/SDL/index.php
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "sdl_playground.h"
#include "sdl_playground.c"
#include "array.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define RADIUS 10

typedef struct
{
    int x;
    int y;
    int direction;
} Atom;

bool circles_collide(Atom* a, Atom* b)
{
    int dx = a->x - b->x;
    int dy = a->y - b->y;
    int distance_squared = dx * dx + dy * dy;
    int radii_sum = RADIUS + RADIUS;
    return distance_squared <= radii_sum * radii_sum;
}

int main()
{
    SDL_Window* win = NULL;
    SDL_Renderer* ren = NULL;
    Array inst;
    array_init(&inst, sizeof(Atom), 1);

    srand(time(NULL));
    bool initialized = sdl_playground_init(&win, &ren, WINDOW_WIDTH, WINDOW_HEIGHT);

    if (!initialized)
    {
        sdl_playground_destroy(win, ren);
        return -1;
    }

    SDL_Event e;
    bool quit = false;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_r)
                {
                    quit = true;
                }
            }
            else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
            {
                Atom* atom = array_push(&inst);
                atom->x = e.motion.x;
                atom->y = e.motion.y;
                atom->direction = rand() % 2 == 0 ? 1 : -1;
            }
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        for (int i = 0; i < array_size(&inst); i++)
        {
            Atom* atom = (Atom*)array_get(&inst, i);

            if (atom->x > WINDOW_WIDTH || atom->x < 0)
            {
                atom->direction *= -1;
            }

            atom->x += atom->direction;

            filledCircleRGBA(ren, atom->x, atom->y, 10, 255, 0, 0, 255);
        }

        for (int i = array_size(&inst) - 1; i >= 0; i--)
        {
            Atom* a = (Atom*)array_get(&inst, i);

            for (int j = i - 1; j >= 0; j--)
            {
                Atom* b = (Atom*)array_get(&inst, j);

                if (circles_collide(a, b))
                {
                    array_remove(&inst, i);
                    array_remove(&inst, j);
                    i--;
                    break;
                }
            }
        }

        for (int i = 0; i < array_size(&inst); i++)
        {
            Atom* atom = (Atom*)array_get(&inst, i);
            filledCircleRGBA(ren, atom->x, atom->y, RADIUS, 255, 0, 0, 255);
        }

        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    array_free(&inst);
    sdl_playground_destroy(win, ren);

    return 0;
}
