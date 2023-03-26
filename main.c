#include "img.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (!argv[1]) {
    printf("Insert file name!\n");
    exit(1);
  }

  char *file_name = argv[1];

  Img image = Image(file_name);

  if (is_png_file(file_name)) {
    image.process_png(image);
  } else {
    image.process(image);
  }

  image.draw(image);
  image.delete(image);
}
