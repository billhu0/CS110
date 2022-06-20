#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("please pass image name!");
    return 0;
  }

  int width, height, nrChannels;
  unsigned char *image = stbi_load(argv[1], &width, &height, &nrChannels, 0);

  uint16_t target_img[width * height];
  printf("channel num is %d\n", (int)nrChannels);
  printf("size of the picture is %d x %d\n", width, height);
  for (int i = 0; i < width * height; i++) {
    unsigned char r = image[nrChannels * i];
    unsigned char g = image[nrChannels * i + 1];
    unsigned char b = image[nrChannels * i + 2];
    unsigned char a;
    if (nrChannels == 4) {
      a = image[nrChannels * i + 3];
    }
    /* change 0 to 1 if you want to convert other color. */
    if (0) {
      /* convert color to RGB565 */
      uint16_t color = r >> 3 << 11;
      color += g >> 2 << 5;
      color += b >> 3;
      uint16_t tmp = color << 8;
      color = tmp + (color >> 8);
      target_img[i] = color;
    } else {
      /* Mark all opaque pixel as white, otherwise black */
      if (a == 255) {
        target_img[i] = 0xffff;
      } else {
        target_img[i] = 0x0000;
      }
    }
  }

  stbi_image_free(image);

  FILE *fp;
  fp = fopen("result.h", "w");
  uint8_t *u8_string = (uint8_t *)target_img;
  fprintf(fp, "unsigned char arr[] = {");
  for (int i = 0; i < width * height * 2; i++) {
    fprintf(fp, "0x%02x", u8_string[i]);
    if (i != width * height * 2 - 1) {
      fprintf(fp, ", ");
    }
  }
  fprintf(fp, "};");
  fclose(fp);

  return 0;
}