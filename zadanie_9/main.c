#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;

typedef struct
{
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

typedef struct
{
    byte b;
    byte g;
    byte r;
} Pixel;

typedef struct
{
    Pixel* pixels;
    TGAHeader header;
    int width;
    int height;
    int size;
} Image;


int tga_header_width(const TGAHeader* self)
{
    int width = 0;
    memcpy(&width, self->width, 2);
    return width;
}

int tga_header_height(const TGAHeader* self)
{
    int height = 0;
    memcpy(&height, self->height, 2);
    return height;
}

int tga_header_size(const TGAHeader* self)
{
    const int header_height = tga_header_height(self);
    const int header_width = tga_header_width(self);
    return header_width * header_height;
}

Pixel* load_pixels(const TGAHeader header, FILE* file)
{
    const int size = tga_header_size(&header);
    Pixel* pixels = malloc(sizeof(Pixel) * size);
    assert(fread(pixels, sizeof(Pixel) * size, 1, file) == 1);
    return pixels;
}

Image load_image(const char* file_name)
{
    FILE* file = fopen(file_name, "rb");

    if (file == NULL)
    {
        printf("Could not load image\n");
        exit(1);
    }

    TGAHeader header;
    fread(&header, sizeof(TGAHeader), 1, file);
    Pixel* pixels = load_pixels(header, file);
    const Image image = {
        pixels, header, tga_header_width(&header), tga_header_height(&header), tga_header_size(&header)
    };
    fclose(file);
    return image;
}

void convert_text(int offset_x, const int offset_y, const Image image, const char* row, const int row_length,
                  const Image* letters)
{
    for (int i = 0; i < row_length; ++i)
    {
        if (row[i] == ' ')
        {
            offset_x += 10;
            continue;
        }

        const int index = row[i] - 'A';
        const Image letter_image = letters[index];

        for (int y = 0; y < letter_image.height; ++y)
        {
            for (int x = 0; x < letter_image.width; ++x)
            {
                const int target_x = offset_x + x;
                const int target_y = offset_y + y;

                const Pixel* letter_pixel = letter_image.pixels + (y * letter_image.width + x);

                if (letter_pixel->r == 255 && letter_pixel->g == 255 && letter_pixel->b == 255)
                {
                    Pixel* image_pixel = image.pixels + (target_y * image.width + target_x);
                    image_pixel->r = 255;
                    image_pixel->g = 255;
                    image_pixel->b = 255;
                }
            }
        }

        offset_x += letter_image.width;
    }
}

void print_image(const int overall_lines, const Image* letters, const Image image, const int top_lines)
{
    char row[100];

    for (int line = 0; line < overall_lines; ++line)
    {
        fgets(row, sizeof row, stdin);
        row[strcspn(row, "\n")] = '\0';

        int row_length = strlen(row);
        int row_width = 0;

        for (int i = 0; i < row_length; ++i)
        {
            row[i] = toupper(row[i]);
        }

        for (int i = 0; i < row_length; ++i)
        {
            if (row[i] == ' ')
            {
                row_width += 7;
            }
            else if (row[i] >= 'A' && row[i] <= 'Z')
            {
                const int index = row[i] - 'A';
                row_width += letters[index].width;
            }
        }

        const int offset_x = (image.width - row_width) / 2;

        if (line >= top_lines)
        {
            const int margin = image.height - ((overall_lines - line) * 40) - 20;
            convert_text(offset_x, margin, image, row, row_length, letters);
        }
        else
        {
            const int margin = (line * 40) + 20;
            convert_text(offset_x, margin, image, row, row_length, letters);
        }
    }
}

int main(const int argc, char* argv[])
{
    if (argc != 4)
    {
        printf("Wrong parameters\n");
        return 1;
    }

    const char* input_file_name = argv[1];
    const char* output_file_name = argv[2];
    const char* font_path = argv[3];
    char row[100];

    if (font_path == NULL)
    {
        exit(1);
    }

    Image letters[26];
    const Image image = load_image(input_file_name);
    FILE* output_file = fopen(output_file_name, "wb");


    fgets(row, sizeof row, stdin);
    const int top_lines = atoi(strtok(row, " "));
    const int bottom_lines = atoi(strtok(NULL, " "));
    const int overall_lines = top_lines + bottom_lines;

    for (int letter = 0; letter < 26; ++letter)
    {
        char letter_path[100];
        sprintf(letter_path, "%s/%c.tga", font_path, 'A' + letter);
        letters[letter] = load_image(letter_path);
    }

    print_image(overall_lines, letters, image, top_lines);

    fwrite(&image.header, sizeof(TGAHeader), 1, output_file);
    fwrite(image.pixels, sizeof(Pixel), image.size, output_file);

    fclose(output_file);
    free(image.pixels);
    for (int letter = 0; letter < 26; ++letter)
    {
        free(letters[letter].pixels);
    }

    return 0;
}
