#include <stdio.h>
#include <stdlib.h>
#include "img.h"

int main(int argc, char ** argv)
{   
    if(!argv[1] || !argv[2]){
        printf("Insert image dimensions!\n");
        exit(1);
    }

    unsigned int width, height;
    sscanf(argv[1], "%d", &width);
    sscanf(argv[2], "%d", &height);

    Img img = Image(width,height);
    img.decode_img(img, "./image-test.jpg");
    img.draw_img(img);
    
    return 0;
}
