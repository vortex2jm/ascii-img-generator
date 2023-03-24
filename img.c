#include "img.h"
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct atributes {
  char *file;
  unsigned int width;
  unsigned int height;
  char **buffer;
};

// constructor
Img Image(char *file);

// public
unsigned int get_width(Img img);
unsigned int get_height(Img img);
void process(Img img);
void draw(Img img);
void delete(Img img);
void process_png(Img img);

// private
char **CreateBuffer(Img img);

// Implementation====================
unsigned int get_width(Img img) { return img.data->width; }

//====================================================//
unsigned int get_height(Img img) { return img.data->height; }

//====================================================//
void process(Img img) {
  // img.data->buffer = CreateBuffer(img);
  const unsigned char density[29] = "N@#W$9876543210?!abc;:+=-,._ ";

  FILE *file = fopen(img.data->file, "rb");
  if (!file) {
    printf("Could not open file %s!\n", img.data->file);
    exit(1);
  }

  // Lendo largura e altura do arquivo
  fscanf(file, "P6\n%d %d\n255\n", &img.data->width, &img.data->height);

  // Criando uma matriz para armazenar a nova imagem
  img.data->buffer = CreateBuffer(img);

  int red = 0, green = 0, blue = 0, avarage = 0, index = 0;

  for (int x = 0; x < img.data->width; x++) {
    for (int y = 0; y < img.data->height; y++) {
      red = fgetc(file);
      green = fgetc(file);
      blue = fgetc(file);

      avarage = (red + green + blue) / 3;

      if (!avarage)
        index = 29 - 1;
      else
        index = avarage % 29;

      img.data->buffer[x][y] = density[index];
    }
  }
  fclose(file);
}

void process_png(Img img) {
  FILE *file = fopen(img.data->file, "rb");

  if (!file) {
    fprintf(stderr, "Could not open file %s!\n", img.data->file);
    exit(1);
  }

  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
    fprintf(stderr, "Error: failed to create PNG read structure\n");
    fclose(file);
    exit(1);
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    fprintf(stderr, "Error: failed to create PNG info structure\n");
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    fclose(file);
    exit(1);
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    fprintf(stderr, "Error: failed to set jump point for PNG read\n");
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(file);
    exit(1);
  }

  png_init_io(png_ptr, file);
  png_read_info(png_ptr, info_ptr);

  int width = png_get_image_width(png_ptr, info_ptr);
  int height = png_get_image_height(png_ptr, info_ptr);
  png_byte color_type = png_get_color_type(png_ptr, info_ptr);
  png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  img.data->width = width;
  img.data->height = height;
  img.data->buffer = CreateBuffer(img);

  if (bit_depth == 16) {
    png_set_strip_16(png_ptr);
  }

  if (color_type == PNG_COLOR_TYPE_PALETTE) {
    png_set_palette_to_rgb(png_ptr);
  }

  if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
    png_set_expand_gray_1_2_4_to_8(png_ptr);
  }

  if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
    png_set_tRNS_to_alpha(png_ptr);
  }

  if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY ||
      color_type == PNG_COLOR_TYPE_PALETTE) {
    png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
  }

  if (color_type == PNG_COLOR_TYPE_GRAY ||
      color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
    png_set_gray_to_rgb(png_ptr);
  }

  png_read_update_info(png_ptr, info_ptr);

  png_bytep *row_pointers = malloc(sizeof(png_bytep) * height);
  for (int y = 0; y < height; y++) {
    row_pointers[y] = malloc(png_get_rowbytes(png_ptr, info_ptr));
  }

  png_read_image(png_ptr, row_pointers);

  char const *density = "N@#W$9876543210?!abc;:+=-,._ ";

  for (int y = 0; y < height; y++) {
    png_bytep row = row_pointers[y];
    for (int x = 0; x < width; x++) {
      png_bytep px = &(row[x * 4]);

      // compute alpha pre-multiplied rgba values
      int a = px[3];
      int r = (px[0] * a) / 255;
      int g = (px[1] * a) / 255;
      int b = (px[2] * a) / 255;

      int idx;
      int avg = (r + g + b) / 3;

      if (avg == 0) {
        idx = strlen(density) - 1;
      } else {
        idx = avg % strlen(density);
      }

      img.data->buffer[y][x] = density[idx];
    }
  }

  fclose(file);
}

//====================================================//
void draw(Img img) {
  for (int l = 0; l < img.data->width; l++) {
    for (int c = 0; c < img.data->height; c++) {
      printf("%c", img.data->buffer[l][c]);
    }
    printf("\n");
  }
  printf("\n");
}

//====================================================//
void delete(Img img) {
  if (img.data) {
    if (img.data->buffer) {
      for (int x = 0; x < img.data->width; x++) {
        free(img.data->buffer[x]);
      }
      free(img.data->buffer);
    }
    free(img.data);
  }
}

//====================================================//
Img Image(char *file) {
  static Img img;

  img.get_width = &get_width;
  img.get_height = &get_height;
  img.process = &process;
  img.process_png = &process_png;
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
char **CreateBuffer(Img img) {
  char **buffer = malloc(sizeof(char *) * img.data->width);
  for (int i = 0; i < img.data->width; i++) {
    buffer[i] = malloc(sizeof(char) * img.data->height);
  }
  return buffer;
}

bool is_png_file(const char *filename) {
  FILE *fp = fopen(filename, "rb");
  if (!fp) {
    printf("Error: failed to open file %s\n", filename);
    return false;
  }

  unsigned char signature[8];
  if (fread(signature, 1, 8, fp) != 8) {
    printf("Error: failed to read file signature\n");
    fclose(fp);
    return false;
  }

  if (png_sig_cmp(signature, 0, 8)) {
    printf("Error: file %s is not a PNG file\n", filename);
    fclose(fp);
    return false;
  }

  fclose(fp);
  return true;
}
