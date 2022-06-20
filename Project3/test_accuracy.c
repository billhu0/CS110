#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <immintrin.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define PI 3.14159

typedef struct FVec
{
    unsigned int length;
    float* data;
} FVec;

typedef struct Image
{
    unsigned int dimX, dimY, numChannels;
    float* data;
} Image;


int main(int argc, char** argv)
{
    float a, x0, x1;
    unsigned int dim;
    
    Image Srcimg;
    Srcimg.data = stbi_loadf(argv[1], &(Srcimg.dimX), &(Srcimg.dimY), &(Srcimg.numChannels), 0);
    
    Image Desimg;
    Desimg.data = stbi_loadf(argv[2], &(Desimg.dimX), &(Desimg.dimY), &(Desimg.numChannels), 0);

    if(Srcimg.dimX != Desimg.dimX || Srcimg.dimY != Desimg.dimY || Srcimg.numChannels!= Desimg.numChannels){
        printf("img size not fit !\n");
        exit(-1);
    }

    // printf("stbi_loadf ： dimx = %d, dimy = %d, channel = %d \n",img.dimX,img.dimY,img.numChannels);
    // unsigned char * ans = malloc(imgOut.dimX * imgOut.dimY * imgOut.numChannels * sizeof(char));
    double delta = 0.0, threshold = 1e-4, avg_delta;
    for (int y = 0; y < Desimg.dimX* Desimg.dimY * Desimg.numChannels; y++)
    {
        delta += (fabs(Desimg.data[y] - Srcimg.data[y]) > 1) ? fabs(Desimg.data[y] - Srcimg.data[y]) : 0;
    }
    avg_delta = delta / (Desimg.dimX* Desimg.dimY * Desimg.numChannels);
    printf("%lf\n", avg_delta);
    if (avg_delta < threshold)
        return 0;
    else
        return -1;
}