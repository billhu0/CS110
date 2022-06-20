This does gaussian blur on a user-input image. It generates a 1-dimensional Gaussian distribution kernel with qualities set by the user.

Requirements: stb_image.h and stb_image_write.h

Usage:   ./gbfloat_base <inputjpg> <outputname> <double: a> <double: x0> <double: x1> <unsigned int: dim> <unsigned int: min dim>

IMPORTANT: parameter dim and min dim must both be odd number!!

Example: ./gbfloat_base test.jpg output.jpg 0.6 -2.0 2.0 101 1

The above is a recommended configuration. It will generate a kernel of 101 samples of a Gaussian distribution function centered at the origin. The 101 evenly-spaced samples are taken on the specified interval, in this case from -2.0 to 2.0. The specified value 'a', in this case 0.6, is a parameter of the Gaussian distribution function.

As in this project, the more the image gets to the center, the less blur it will be, so setting the min dim can change how blur will the center of the image be. You can play with some different min dim to see how the image changes.

The blurring process is done in two steps; Given image A as our input, we first convolve the kernel over the rows of image A to produce a horizontally blurred image B. We then convolve the kernel over the columns of image B to produce a horizontally and vertically blurred image C. The image C is our final blurred image, and we save it to disk.

Image reading and writing is handled by stb_image.h and stb_image_write.h.