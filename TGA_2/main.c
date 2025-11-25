#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
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
typedef struct {
    int width;
    int height;
    Pixel* pixels;
    TGAHeader header;
} Image;
Image load_image(const char * filename) {
    FILE * file = fopen(filename, "rb");
    TGAHeader header = {0};
    fread(&header, sizeof(TGAHeader), 1, file);
    int width = tga_header_width(&header);
    int height = tga_header_height(&header);
    Pixel* pixels = (Pixel*) malloc(sizeof(Pixel) * width * height);
    fread(pixels, sizeof(Pixel) * width * height, 1, file);
    fclose(file);
    return (Image){width, height, pixels, header};
}
void write_text(Image image, const char * filename) {
    FILE * output_file = fopen(filename, "wb");
    fwrite(&image.header, sizeof(TGAHeader), 1, output_file);
    fwrite(image.pixels, sizeof(Pixel) * image.width * image.height, 1, output_file);
    fclose(output_file);
}

void text_to_image(int offset_x, int offset_y, Image image, char* row, int len, Image* alphabet){
    for(int j = 0; j < len; j++){
        if(row[j] == ' '){
            offset_x += 7;
            continue;
        }
        int index = row[j] - 'A';
        Image font_image = alphabet[index];
        for(int y = 0; y < font_image.height; y++){
            for(int x = 0; x < font_image.width; x++){
                Pixel* font_pixel = font_image.pixels + (y * font_image.width + x);
                if(!(font_pixel->red == 0 && font_pixel->green == 0 && font_pixel->blue == 0)){
                    Pixel* image_pixel = image.pixels + ((offset_y + y) * image.width + (offset_x + x));
                    *image_pixel = *font_pixel;
                    font_pixel->red = 255;
                    font_pixel->green = 255;
                    font_pixel->blue = 255;
                }
            }
        }
        offset_x += font_image.width;
    }
}
int main(int argc, char** argv){
    if(argc != 4){
        printf("Wrong parameters\n");
        return 1;
    }
    char *input = argv[1];
    char *output = argv[2];
    char *fonts = argv[3];
    FILE* file = fopen(input, "rb");
    if(file == NULL){
        printf("Could not load image\n");
        return 1;
    }
    fclose(file);
    Image image = load_image(input);
    char number_of_rows[101] = {0};
    fgets(number_of_rows, sizeof(number_of_rows), stdin);
    char *rows = strtok(number_of_rows, " ");
    int upper = atoi(rows);
    rows = strtok(NULL, " ");
    int lower = atoi(rows);
    int total = upper + lower;
    Image alphabet[26];
    for(int i = 0; i < 26; i++){
        char font_path[101] = {0};
        sprintf(font_path, "%s/%c.tga", fonts, 'A' + i);
        alphabet[i] = load_image(font_path);
    }
    for(int i = 0; i < total; i++){
        char row[101] = {0};
        fgets(row, sizeof(row), stdin);
        int len = strlen(row);
        if(row[len-1] == '\n'){
            row[len-1] = '\0';
        }
        len = strlen(row);
        for(int j = 0; j < len; j++){
            row[j] = toupper(row[j]);
        }
        int text_width = 0;
        for(int j = 0; j < len; j++){
            if(row[j] == ' '){
                text_width += 7;
            }
            if(row[j] >= 'A' && row[j] <= 'Z'){
                int index = row[j] - 'A';
                text_width += alphabet[index].width;
            }
        }
        if(i >= upper){
            int offset_x = (image.width - text_width) / 2;
            int offset_y = image.height - ((total - i) * 34) - 6;
            text_to_image(offset_x, offset_y, image, row, len, alphabet);
        }else{
            int offset_x = (image.width - text_width) / 2;
            int offset_y = (i * 34) + 6;
            text_to_image(offset_x, offset_y, image, row, len, alphabet);
        }
    }
    write_text(image, output);
    return 0;
}