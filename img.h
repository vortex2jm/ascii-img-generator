#ifndef img_h
#define img_h

typedef struct atributes Atributes;
typedef struct img Img;

struct img{
    Atributes * data;
    unsigned int(*get_width)(Img);
    unsigned int(*get_height)(Img);
    void(*process)(Img);
    void(*draw)(Img);
    void(*delete)(Img);
};

Img Image(char * file);

#endif
