# Tips

In `image` folder, you can find some useful images if you want to implement dino runner. All images used in the demo video is listed in this folder. They have been scaled to proper size such that they can be drawn on screen of Longan Nano board properly.

`img.h` contains 11 byte arrays, correspond to the images in `image` folder. You can include this header file in your project and pass the array to `LCD_ShowPicture()`.

`all_elem.png` include all elements in the original game. If you want to make your game looks better, you can crop the region you want to use.

`converter.c` is a very simple tool that converts the image to a byte array and store the array in `result.h`. By default, it assign all opaque pixels to white, and other pixels to black. Compile it with flag `-lm` and run it with `./converter <image_name>`. 

We also provide the code to convert other color in the *else* statement, which convert RGB888 to RGB565.