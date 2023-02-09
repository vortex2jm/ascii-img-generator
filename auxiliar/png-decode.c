#include <stdio.h>
#include <png.h>

int main(int argc, char *argv[]) {
  FILE *fp = fopen("input.png", "rb");
  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info = png_create_info_struct(png);
  png_init_io(png, fp);
  png_read_info(png, info);

  int width = png_get_image_width(png, info);
  int height = png_get_image_height(png, info);
  int color_type = png_get_color_type(png, info);
  int bit_depth = png_get_bit_depth(png, info);

  png_bytep row_pointers[height];
  for (int y = 0; y < height; y++) {
    row_pointers[y] = (png_bytep)malloc(png_get_rowbytes(png, info));
  }
  png_read_image(png, row_pointers);

  FILE *out = fopen("output.raw", "wb");
  for (int y = 0; y < height; y++) {
    fwrite(row_pointers[y], 1, png_get_rowbytes(png, info), out);
    free(row_pointers[y]);
  }
  fclose(fp);
  fclose(out);
  png_destroy_read_struct(&png, &info, NULL);
  return 0;
}
