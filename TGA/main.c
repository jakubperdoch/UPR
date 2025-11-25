#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

typedef unsigned char byte;

typedef struct {
    byte id_length;
    byte color_map_type;
    byte image_type;
    byte color_map[5];
    byte x_origin[2];
    byte y_origin[2];
    byte width[2];
    byte height[2];
    byte depth;
    byte descriptor;
} TGAHeader;

int tga_header_width(TGAHeader * self){
    int width = 0;

    memcpy(&width, self->width, 2);
    return width;
}

int tga_header_height(TGAHeader * self){
    int height = 0;

    memcpy(&height, self->height, 2);
    return height;
}

typedef struct {
    byte blue;
    byte green;
    byte red;
} Pixel;

Pixel* load_pixels(TGAHeader header, FILE* file) {
    int width = tga_header_width(&header);
    int height = tga_header_height(&header);

    Pixel* pixels = (Pixel*) malloc(sizeof(Pixel) * width * height);
    assert(fread(pixels, sizeof(Pixel) * width * height, 1, file) == 1);
    return pixels;
}

void write_pixels(TGAHeader header, const Pixel * pixels, const char * filename) {
    int width = tga_header_width(&header);
    int height = tga_header_height(&header);

    FILE * output_file = fopen(filename, "wb");
    assert(output_file);
    assert(fwrite(&header, sizeof(TGAHeader), 1, output_file) == 1);
    assert(fwrite(pixels, sizeof(Pixel) * width * height, 1, output_file) == 1);
}

void draw_rect(TGAHeader header, Pixel * pixels, const Pixel c, const int x, const int y, const int w, const int h){
    int width = tga_header_width(&header);
    int height = tga_header_height(&header);
    int final_y = (y + h) >= height ? height : (y + h);
    int final_x = (x + w ) >= width ? width : (x + w);
    for (int row = y; row < final_y; row++) {
        for (int col = x; col < final_x; col++) {
            Pixel* pixel = pixels + (row * width + col);
            pixel->red = c.red;
            pixel->blue = c.blue;
            pixel->green = c.green;
        }
    }
}


int main(){
    FILE* file = fopen("carmack.tga", "rb");
    assert(file);

    TGAHeader header = {};
    assert(fread(&header, sizeof(TGAHeader), 1, file) == 1);

    printf("Image type: %d, pixel depth: %d\n", header.image_type, header.depth);

    int width = tga_header_width(&header);
    int height = tga_header_height(&header);

    printf("w=%d, h=%d\n", width, height);

    Pixel* pixels = load_pixels(header, file);
    fclose(file);
    Pixel c = {.red = 30, .green = 120, .blue = 100};
    draw_rect(header, pixels, c, 200, 200, 100, 40);
    write_pixels(header, pixels, "idk.tga");


    return 0;
}