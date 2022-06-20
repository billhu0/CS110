#include <immintrin.h>
#include <math.h>
#include <omp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define PI 3.14159
#define NUM_THREADS 4
#define DEBUG

typedef struct FVec {
    int    length;
    int    min_length;
    int    min_deta;
    float* data;
    float* sum;
    float* flatten_data;
} FVec;

typedef struct Image {
    int    dimX, dimY, numChannels;
    float* data;
} Image;

void normalize_FVec(FVec v) {
    int ext  = v.length / 2;
    v.sum[0] = v.data[ext];
    for (int i = ext + 1, j = 1; i < v.length; i++, j++) {
        v.sum[j] = v.sum[j - 1] + v.data[i] * 2;
    }
}

float* get_pixel(Image img, int x, int y) {
    if (x < 0) x = 0;
    if (x >= img.dimX) x = img.dimX - 1;
    if (y < 0) y = 0;
    if (y >= img.dimY) y = img.dimY - 1;
    return img.data + 3 * (y * img.dimX + x);  // 'img.numChannels' is changed to 3
}

float gd(float a, float b, float x) {
    float c = (x - b) / a;
    return exp((-.5) * c * c) / (a * sqrt(2 * PI));
}

FVec make_gv(float a, float x0, float x1, int length, int min_length) {
    FVec v;
    v.length     = length;
    v.min_length = min_length;
    if (v.min_length > v.length) {
        v.min_deta = 0;
    } else {
        v.min_deta = ((v.length - v.min_length) / 2);
    }
    v.data       = malloc(length * sizeof(float));
    v.sum        = malloc((length / 2 + 1) * sizeof(float));
    float step   = (x1 - x0) / ((float)length);
    int   offset = length / 2;

    for (int i = 0; i < length; i++) {
        v.data[i] = gd(a, 0.0f, (i - offset) * step);
    }
    normalize_FVec(v);
    return v;
}

Image img_sc(Image a) {
    Image b = a;
    b.data  = malloc((b.dimX * b.dimY * 3 /* + 64 */) * sizeof(float));
    // replaced 'b.numChannels' with '3' here
    return b;
}

// Functions gb_h and gb_v takes almost 100% of the execution time.
// We need to mainly focus on these two functions.

Image gb_h(Image a, FVec gv) {
    Image     b   = img_sc(a);
    const int ext = gv.length >> 1;

    // flatten pixels here, making them continous in memory
    float* new_pixels = (float*)malloc(((a.dimX + 2 * ext) * a.dimY * 3) * sizeof(float));
    #pragma omp parallel for schedule(dynamic)
    for (int y = 0; y < (int)a.dimY; ++y) {
        for (int x = 0 - ext; x < (int)a.dimX + ext; ++x) {
            float* old_pixel = get_pixel(a, x, y);
            // original get_pixel function returns 3 * (y * img.dimX + x)
            new_pixels[3 * (y * (2 * ext + a.dimX) + x + ext) + 0] = old_pixel[0];
            new_pixels[3 * (y * (2 * ext + a.dimX) + x + ext) + 1] = old_pixel[1];
            new_pixels[3 * (y * (2 * ext + a.dimX) + x + ext) + 2] = old_pixel[2];
        }
    }

    #pragma omp parallel for schedule(dynamic)
    for (int y = 0; y < a.dimY; ++y) {
        for (int x = 0; x < a.dimX; ++x) {
            float* pc   = get_pixel(b, x, y);
            int    deta = fmin(fmin(a.dimY - y - 1, y), fmin(a.dimX - x - 1, x));
            deta        = fmin(deta, gv.min_deta);

            // Since image pixels are stored continuously in memory, like R G B R G B R G ...,
            // we calculate R, G, B one by one here, instead of calculating each channel separately.
            // This is more cache-friendly, and avoids triple calculation of pc, deta, and some other variables.

            #define OFFSET_GET_PIXEL(xxx, yyy) (3 * (yyy * (2 * ext + a.dimX) + xxx + i))

            __m256 sumA = _mm256_setzero_ps();
            __m256 sumB = _mm256_setzero_ps();
            __m256 sumC = _mm256_setzero_ps();

            int i;
            for (i = deta; i < gv.length - deta - 8; i += 8) {
                sumA = _mm256_fmadd_ps(_mm256_loadu_ps(gv.flatten_data + i * 3),
                                       _mm256_loadu_ps(new_pixels + OFFSET_GET_PIXEL(x, y)), sumA);
                sumB = _mm256_fmadd_ps(_mm256_loadu_ps(gv.flatten_data + i * 3 + 8),
                                       _mm256_loadu_ps(new_pixels + OFFSET_GET_PIXEL(x, y) + 8), sumB);
                sumC = _mm256_fmadd_ps(_mm256_loadu_ps(gv.flatten_data + i * 3 + 16),
                                       _mm256_loadu_ps(new_pixels + OFFSET_GET_PIXEL(x, y) + 16), sumC);
            }

            // store the result (deal with the tail later)
            float arrA[8], arrB[8], arrC[8];
            _mm256_storeu_ps(arrA, sumA);
            _mm256_storeu_ps(arrB, sumB);
            _mm256_storeu_ps(arrC, sumC);

            float sum_r = arrA[0] + arrA[3] + arrA[6] + arrB[1] + arrB[4] + arrB[7] + arrC[2] + arrC[5];
            float sum_g = arrA[1] + arrA[4] + arrA[7] + arrB[2] + arrB[5] + arrC[0] + arrC[3] + arrC[6];
            float sum_b = arrA[2] + arrA[5] + arrB[0] + arrB[3] + arrB[6] + arrC[1] + arrC[4] + arrC[7];

            // deal with the tail
            for (; i < gv.length - deta; ++i) {
                int offset = i - ext;
                sum_r += gv.data[i] * get_pixel(a, x + offset, y)[0];
                sum_g += gv.data[i] * get_pixel(a, x + offset, y)[1];
                sum_b += gv.data[i] * get_pixel(a, x + offset, y)[2];
            }

            pc[0] = sum_r / gv.sum[ext - deta];
            pc[1] = sum_g / gv.sum[ext - deta];
            pc[2] = sum_b / gv.sum[ext - deta];
        }
    }
    free(new_pixels);
    return b;
}

// This function transponse the image matrix, or in other words, 'rotate' the image.
// Instead of gb_h and gb_v, we use gb_h twice to improve cache hit rate.
void transponse(Image* src, Image* dst) {
    dst->dimX        = src->dimY;
    dst->dimY        = src->dimX;
    dst->numChannels = 3;
    dst->data        = (float*)malloc((dst->dimX * dst->dimY * 3 + 64) * sizeof(float));
    #pragma omp parallel for schedule(dynamic)
    for (int src_y = 0; src_y < src->dimY; src_y++) {
        for (int src_x = 0; src_x < src->dimX; src_x++) {
            dst->data[3 * (src_x * dst->dimX + src_y) + 0] = src->data[3 * (src_y * src->dimX + src_x) + 0];
            dst->data[3 * (src_x * dst->dimX + src_y) + 1] = src->data[3 * (src_y * src->dimX + src_x) + 1];
            dst->data[3 * (src_x * dst->dimX + src_y) + 2] = src->data[3 * (src_y * src->dimX + src_x) + 2];
        }
    }
}

Image apply_gb(Image a, FVec gv) {
    // flatten gv.data here, extend the array by 3
    gv.flatten_data = (float*)malloc((gv.length * 3) * sizeof(float));
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < gv.length; i++) {
        gv.flatten_data[i * 3 + 0] = gv.data[i];
        gv.flatten_data[i * 3 + 1] = gv.data[i];
        gv.flatten_data[i * 3 + 2] = gv.data[i];
    }
    // do horizontal blur
    Image b = gb_h(a, gv);
    Image trans_b;
    transponse(&b, &trans_b);
    free(b.data);
    // do vertical blur
    Image c = gb_h(trans_b, gv);
    free(trans_b.data);
    Image result;
    // transpose it back
    transponse(&c, &result);
    free(c.data);
    free(gv.flatten_data);
    // free unused data
    return result;
}

int main(int argc, char** argv) {
    struct timeval start_time, stop_time, elapsed_time;
    gettimeofday(&start_time, NULL);
    if (argc < 6) {
        printf("Usage: ./gb.exe <inputjpg> <outputname> <float: a> <float: x0> <float: x1> <unsigned int: dim>\n");
        exit(0);
    }

    float a, x0, x1;
    int   dim, min_dim;

    sscanf(argv[3], "%f", &a);
    sscanf(argv[4], "%f", &x0);
    sscanf(argv[5], "%f", &x1);
    sscanf(argv[6], "%d", &dim);
    sscanf(argv[7], "%d", &min_dim);

    FVec  v = make_gv(a, x0, x1, dim, min_dim);
    Image img;
    img.data     = stbi_loadf(argv[1], &(img.dimX), &(img.dimY), &(img.numChannels), 0);
    Image imgOut = apply_gb(img, v);
    stbi_write_jpg(argv[2], imgOut.dimX, imgOut.dimY, imgOut.numChannels, imgOut.data, 90);
    gettimeofday(&stop_time, NULL);
    timersub(&stop_time, &start_time, &elapsed_time);
    printf("%f \n", elapsed_time.tv_sec + elapsed_time.tv_usec / 1000000.0);
    free(imgOut.data);
    free(v.data);
    free(v.sum);
    return 0;
}
