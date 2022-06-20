# Project 4: Longan Nano minigame


## ℹ️ Overview

In this project, we implemented a Chrome-Dino game running on Longan Nano development board. 

A [demo video](https://autolab.sist.shanghaitech.edu.cn/gitlab/cs110_22s_projects/p4_hulj_wuyh4/-/blob/main/Demo%20Video.mp4) is provided.


## 🌟 Highlights

This game features

- A simple startup menu and difficulty selection page

- A score board

- Randomly generated cactus and pterosaurs acting like obstacles

- Dino can jump or creep controlled by the 2 buttons

- Super mode in which the dino can hit everything without failing the game


## 🚀 Usage instructions

To compile this project and download it to the board, run 

```
make
make download
```


## Code structure

The file structure of this repo is

```
.
├── autolab.txt
├── Demo Video.mp4
├── dfu-util
├── include
│   ├── fatfs
│   │   ├── diskio.h
│   │   ├── ffconf.h
│   │   ├── ff.h
│   │   └── tf_card.h
│   ├── gd32vf103_libopt.h
│   ├── gd32v_pjt_include.h
│   ├── img.h
│   ├── lcd
│   │   ├── bmp.h
│   │   ├── lcd.h
│   │   └── oledfont.h
│   ├── README
│   ├── systick.h
│   └── utils.h
├── LICENSE
├── Makefile
├── platformio.ini
├── README.md
└── src
    ├── assembly
    │   ├── example.S
    │   ├── func_main.S
    │   ├── func_print_select_mode.S
    │   ├── func_show_black.S
    │   ├── func_show_picture.S
    │   ├── func_show_str_dyn.S
    │   └── func_show_welcome_text.S
    ├── fatfs
    │   ├── 00history.txt
    │   ├── 00readme.txt
    │   ├── ff.c
    │   ├── ffsystem.c
    │   ├── ffunicode.c
    │   └── tf_card.c
    ├── lcd
    │   └── lcd.c
    ├── main.c
    ├── systick.c
    └── utils.c
```
