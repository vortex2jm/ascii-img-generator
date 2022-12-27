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
    int w = img.get_width(img);
    int h = img.get_height(img);
    printf("%d, %d", w, h);
    
    return 0;
}
