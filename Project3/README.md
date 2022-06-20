# Project 3: Gaussian Blur Optimization

For more details please refer to the [course page](https://robotics.shanghaitech.edu.cn/courses/ca/22s/projects/3/).

In this project, we hope you can use all knowledge about computer architecture that your have learnt in this course to optimize the Gaussian Blur algorithm.

## Gaussian Blur

In image processing, a Gaussian blur (also known as Gaussian smoothing) is the result of blurring an image by a Gaussian function. It is a widely used effect in graphics software, typically to reduce image noise and reduce detail. The visual effect of this blurring technique is a smooth blur resembling that of viewing the image through a translucent screen.

Mathematically, applying a Gaussian blur to an image is the same as convolving the image with a Gaussian function.

In this project, we adopt a 1-dimensional Gaussian distribution kernel with qualities set by the user, and the blurring process is done in two steps: Given image A as our input, we first convolve the kernel over the rows of image A to produce a horizontally blurred image B. We then convolve the kernel over the columns of image B to produce a horizontally and vertically blurred image C. The image C is our final blurred image, and we save it to disk. Image reading and writing is handled by `stb_image.h` and `stb_image_write.h`.

## Optimization Techniques

To test the optimization, you may use unnecessary huge Gaussian kernels (size 500+) to test the speed of the program. You can find many obvious optimizations in the implementation we provide, with what you have learnt in Computer Architecture. We are listing some of the possible approaches below:

### Algorithm

You may find there are faster algorithms to do Gaussian Blur. You are not allowed to optimize the naive algorithm we give though, as this is not the focus of Computer Architecture. You will receive no point if we find you do that.

### Compiler

There are some optimization flags that can be turned on in `GCC`. The available flags for `x86` ISA from `GCC` is listed here. However, we wish you to do the optimization on your own, instead of relying on the compiler to do it for you. You will receive 0 points if you try to turn on any other optimization flags except for `-O2` specified in Makefile.

### Multi-threading

The first and the easiest approach is to use multi-threading to optimize this algorithm, with either `pthread` or `OpenMP`.

### SIMD instructions

Part of this algorithm is also a good candidate for SIMD instructions.

### Loop unrolling

Loop unrolling can work very well in combination with SIMD instructions, and you should think about it.

### Cache Blocking

Part of this algorithm is also a good candidate for cache blocking.
