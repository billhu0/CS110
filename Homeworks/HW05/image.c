#include "image.h"

void write_image(const char *path, vec3 *image, int image_width, int image_height)
{
    FILE *f;
    int i;
    f = fopen(path, "w");
    fprintf(f, "P3\n%d %d\n%d\n", image_width, image_height, 255);
    for (i = 0; i < image_width * image_height; i++)
        fprintf(f,"%d %d %d ", to_rgb(image[i].x), to_rgb(image[i].y), to_rgb(image[i].z));
    fclose(f);
}