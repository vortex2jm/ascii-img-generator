#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "img.h"

struct atributes{
    char * file;
    unsigned int width;
    unsigned int height;
    char ** buffer;
};

// constructor
Img Image(char * file);

// public
unsigned int get_width(Img img);
unsigned int get_height(Img img);
void process(Img img);
void draw(Img img);
void delete(Img img);

// private
char ** CreateBuffer(Img img);

// Implementation====================
unsigned int get_width(Img img){
    return img.data->width;
}

//====================================================//
unsigned int get_height(Img img){
 return img.data->height;
}

//====================================================//
void process(Img img){
    // img.data->buffer = CreateBuffer(img);
    const unsigned char density[29] = "N@#W$9876543210?!abc;:+=-,._ ";

    FILE * file = fopen(img.data->file, "rb");
    if(!file){
        printf("Could not open file %s!\n", img.data->file);
        exit(1);
    }

    // Lendo largura e altura do arquivo
    fscanf(file, "P6\n%d %d\n255\n", &img.data->width, &img.data->height);

    // Criando uma matriz para armazenar a nova imagem
    img.data->buffer = CreateBuffer(img);

    int red=0, green=0, blue=0, avarage=0, index=0;

    for(int x=0; x<img.data->width; x++){
        for(int y=0; y<img.data->height; y++){
            red = fgetc(file);
            green = fgetc(file);
            blue = fgetc(file);

            avarage = (red + green + blue)/3;

            if(!avarage)
                index = 29 - 1;
            else
                index = avarage % 29;

            img.data->buffer[x][y] = density[index];
        }
    }
    fclose(file);
}

//====================================================//
void draw(Img img){
    for(int l=0; l<img.data->width; l++){
        for(int c=0; c<img.data->height; c++){
            printf("%c", img.data->buffer[l][c]);
        }
        printf("\n");
    }
    printf("\n");
}

//====================================================//
void delete(Img img){
    if(img.data){
        if(img.data->buffer){
            for(int x=0; x < img.data->width; x++){
                free(img.data->buffer[x]);
            }
            free(img.data->buffer);
        }
        free(img.data);
    }
}

//====================================================//
Img Image(char * file){
    static Img img;

    img.get_width = &get_width;
    img.get_height = &get_height;
    img.process = &process;
    img.draw = &draw;
    img.delete = &delete;

    img.data = malloc(sizeof(Atributes));
    img.data->file = file;
    img.data->width = 0;
    img.data->height = 0;
    img.data->buffer = NULL;

    return img;
}

//====================================================//
char ** CreateBuffer(Img img){
    char ** buffer = (char **)malloc(sizeof(char*) * img.data->width);
    for(int i=0;i<img.data->width;i++){
        buffer[i] = (char *)malloc(sizeof(char) * img.data->height);
    }
    return buffer;
}