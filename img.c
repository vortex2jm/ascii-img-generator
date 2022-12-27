#include <stdio.h>
#include <stdlib.h>
#include "img.h"

struct atributes{
    unsigned int width;
    unsigned int height;
    unsigned int rgb[3];
    unsigned char ** buffer;
};

unsigned int get_width(Img img){
    return img.data->width;
}

unsigned int get_height(Img img){
 return img.data->height;
}

void decode_img(Img img, char * path){

    FILE * file = fopen(path, "rb");

    // Decode

    fclose(file);
}

void draw_img(Img img){

}

void f_img(){

}

Img Image(const unsigned int width, const unsigned int height){
    static Img img;

    img.get_width = &get_width;
    img.get_height = &get_height;

    img.data = malloc(sizeof(Atributes));
    img.data->height = height;
    img.data->width = width;
    
    for(int i=0;i<3;i++){
        img.data->rgb[i] = 0;
    }
    
    img.data->buffer = NULL;

    return img;
}
