#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "img.h"

struct atributes{
    unsigned int width;
    unsigned int height;
    unsigned int rgb[3];
    char ** buffer;
};

// constructor
Img Image(const unsigned int width, const unsigned int height);

// public
unsigned int get_width(Img img);
unsigned int get_height(Img img);
void decode_img(Img img, char * path);
void draw_img(Img img);
void f_img();

// private
char ** CreateBuffer(Img img);

// Implementation====================
unsigned int get_width(Img img){
    return img.data->width;
}

unsigned int get_height(Img img){
 return img.data->height;
}


void decode_img(Img img, char * path){
    const unsigned int w = img.data->width;
    const unsigned int h = img.data->height;
    img.data->buffer = CreateBuffer(img);
    const unsigned char density[29] = "N@#W$9876543210?!abc;:+=-,._ ";

    FILE * file = fopen(path, "rb");
    if(!file){
        printf("Could not open file %s!\n", path);
        exit(1);
    }

    int i=1, l=0, c=0, avarage=0, index=0;
    unsigned char r, g, b, a, byte;

    printf("1\n");
    
    int x=1;
    while(fread(&byte, sizeof(unsigned char), 1, file)){

        printf("%d\n",x);
        x++;

        if(i == 1){
            r = byte;
            i++;
        }
        else if(i == 2){
            g = byte;
            i++;
        }
        else if(i == 3){
            b = byte;

            // Generating RGB avarage======//
            avarage = (int)((r+g+b)/3);
            if(!avarage){
                index  = strlen(density) - 1;
            }else{
                index = (avarage % strlen(density));
            }

            // Writing char map=======//
            if(l < h - 1){
                if(c == w - 1){
                    l++;
                    c=0;
                }
                img.data->buffer[l][c] = density[index];
                c++;

            }else if(l == h - 1){
                if(c == w - 1){
                    img.data->buffer[l][c] = density[index];
                    l++;
                }
                img.data->buffer[l][c] = density[index];
                c++;
            }
            i++;
        }else if(i == 4){
            i=1;
        }
    }
    fclose(file);
}

void draw_img(Img img){
    for(int l=0; l<img.data->height; l++){
        for(int c=0; c<img.data->width; c++){
            printf("%c", img.data->buffer[l][c]);
        }
        printf("\n");
    }
    printf("\n");
}

void f_img(){

}

Img Image(const unsigned int width, const unsigned int height){
    static Img img;

    img.get_width = &get_width;
    img.get_height = &get_height;
    img.decode_img = &decode_img;
    img.draw_img = &draw_img;

    img.data = malloc(sizeof(Atributes));
    img.data->height = height;
    img.data->width = width;
    
    for(int i=0;i<3;i++){
        img.data->rgb[i] = 0;
    }
    
    img.data->buffer = NULL;

    return img;
}

char ** CreateBuffer(Img img){
    char ** buffer = (char **)malloc(sizeof(char*) * img.data->height);
    for(int i=0;i<img.data->height;i++){
        buffer[i] = (char *)malloc(sizeof(char) * img.data->width);
    }
    return buffer;
}