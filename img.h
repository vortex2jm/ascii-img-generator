#ifndef img_h
#define img_h

typedef struct atributes Atributes;
typedef struct img Img;

struct img{
    Atributes * data;
    unsigned int(*get_width)(Img);
    unsigned int(*get_height)(Img);
    void(*decode_img)(Img, char *);
    void(*draw_img)(Img);
    void(*f_img)(Img);
};

Img Image(const unsigned int width, const unsigned int height);

#endif
