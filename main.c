#include <stdio.h>
#include <stdlib.h>
#include "img.h"

int main(int argc, char ** argv)
{   
    if(!argv[1]){
        printf("Insert file name!\n");
        exit(1);
    }

    Img image = Image(argv[1]);
    image.process(image);
    image.draw(image);
    image.delete(image);

    return 0;
}
