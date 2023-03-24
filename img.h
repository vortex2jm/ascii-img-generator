#ifndef img_h
#define img_h

#include <stdbool.h>

typedef struct atributes Atributes;
typedef struct img Img;

struct img{
    Atributes * data;
    unsigned int(*get_width)(Img);
    unsigned int(*get_height)(Img);
    void(*process)(Img);
    void(*process_png)(Img);
    void(*draw)(Img);
    void(*delete)(Img);
};

Img Image(char * file);
bool is_png_file(const char *filename);

#endif
