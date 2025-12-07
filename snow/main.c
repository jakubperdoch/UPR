#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "sdl.h"
#include "dynamic_array.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct
{
    int x, y;
    int direction;
    int speed;
    int size;
} SnowFlake;


int main()
{
    SDL_Renderer* renderer = NULL;
    SDL_Context context = sdl_context_init("SnowFlakes", WINDOW_WIDTH, WINDOW_HEIGHT);
    dynarray array;

    srand(time(NULL));
    dynarray_init(&array, 1);

    if (!context.renderer || !context.window)
    {
        sdl_context_free(&context);
        return 1;
    }

    SDL_Texture* texture = IMG_LoadTexture(context.renderer, "Snowflake.svg");
    if (!texture)
    {
        fprintf(stderr, "Failed to load texture: %s\n", IMG_GetError());
        sdl_context_free(&context);
        return 1;
    }

    SDL_Event event;
    bool running = true;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
            {
                SnowFlake* snowflake = malloc(sizeof(SnowFlake));
                snowflake->x = event.button.x;
                snowflake->y = event.button.y;
                snowflake->direction = (rand() % 2 == 0 ? 1 : -1);
                snowflake->speed = rand() % 10 + 1;
                snowflake->size = rand() % 3 + 1;

                dynarray_push(&array, snowflake);
            }
        }

        SDL_SetRenderDrawColor(context.renderer, 0, 0, 0, 255);
        SDL_RenderClear(context.renderer);

        for (int i = 0; i < array.size; i++)
        {
            SnowFlake* flake = (SnowFlake*)array.items[i];

            flake->y += flake->speed;

            flake->direction += flake->direction > 0 ? 2 : -2;

            if (flake->y > WINDOW_HEIGHT)
            {
                dynarray_remove(&array, flake);
                continue;
            }

            SDL_Rect dest;
            dest.w = flake->size * 32;
            dest.h = flake->size * 32;
            dest.x = flake->x;
            dest.y = flake->y;

            SDL_RenderCopyEx(context.renderer, texture, NULL, &dest, flake->direction, NULL, SDL_FLIP_NONE);
        }

        SDL_RenderPresent(context.renderer);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(texture);
    dynarray_free(&array);
    sdl_context_free(&context);


    return 0;
}
