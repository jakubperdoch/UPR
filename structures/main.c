#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Canvas_ Canvas;
typedef struct Player_ Player;

typedef struct
{
    int x;
    int y;
} Position;

struct Canvas_
{
    int width;
    int height;
    char* canvas;
};

struct Player_
{
    Position position;
    Position velocity;
};

int index_2d_na_1d(int radek, int sloupec, int sirka)
{
    return radek * sirka + sloupec;
}

void canvas_new(Canvas* self, const int width, const int height)
{
    self->width = width;
    self->height = height;
    self->canvas = (char*)malloc(width * height * sizeof(char));
}

void canvas_clear(Canvas* self)
{
    const int width = self->width;
    const int height = self->height;

    for (int i = 0; i < width * height; i++)
    {
        self->canvas[i] = ' ';
    }
}

void canvas_draw_edges(Canvas* self)
{
    const int width = self->width;
    const int height = self->height;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
            {
                self->canvas[index_2d_na_1d(i, j, width)] = '#';
            }
        }
    }
}

void canvas_print(Canvas* self)
{
    const int width = self->width;
    const int height = self->height;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%c", self->canvas[index_2d_na_1d(i, j, width)]);
        }

        printf("\n");
    }
}

void canvas_draw_player(Canvas* self, const Player* player)
{
    self->canvas[index_2d_na_1d(player->position.y, player->position.x, self->width)] = 'O';
}

void player_apply_speed(Player* self, const int width, const int height)
{
    self->position.x += self->velocity.x;
    self->position.y += self->velocity.y;

    if (self->position.x == 1 || self->position.x == width - 2)
    {
        self->velocity.x *= -1;
    }

    if (self->position.y == 1 || self->position.y == height - 2)
    {
        self->velocity.y *= -1;
    }
}

int main(void)
{
    const int width = 15;
    const int height = 10;
    Canvas canvas;
    Player player = {.position.x = 10, .position.y = 7, .velocity.x = 1, .velocity.y = 1};

    canvas_new(&canvas, width, height);


    while (1)
    {
        // Canvas Setup
        canvas_clear(&canvas);
        canvas_draw_edges(&canvas);

        // Player actions
        canvas_draw_player(&canvas, &player);
        player_apply_speed(&player, width, height);

        canvas_print(&canvas);
        printf("\033[H\033[J");
        usleep(400 * 1000);
    }

    free(canvas.canvas);

    return 0;
}
