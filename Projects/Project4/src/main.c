#include <stdio.h>
#include <string.h>

#include "lcd/lcd.h"
#include "utils.h"
#include "img.h"

#define BUILTIN_RED   GPIO_PIN_13
#define BUILTIN_GREEN GPIO_PIN_1
#define BUILTIN_BLUE  GPIO_PIN_2
#define RED_ON()    gpio_bit_reset(GPIOC, BUILTIN_RED)
#define GREEN_ON()  gpio_bit_reset(GPIOA, BUILTIN_GREEN)
#define BLUE_ON()   gpio_bit_reset(GPIOA, BUILTIN_BLUE)
#define RED_OFF()   gpio_bit_set(GPIOC, BUILTIN_RED)
#define GREEN_OFF() gpio_bit_set(GPIOA, BUILTIN_GREEN)
#define BLUE_OFF()  gpio_bit_set(GPIOA, BUILTIN_BLUE)

#define TIME_INTERVAL(T) (SystemCoreClock / 4000.0 * (T))

/******************************************************************************
	   Initialize
******************************************************************************/

void longan_led_init() {
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1);
    gpio_init(GPIOA, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ, GPIO_PIN_4);
}

void IO_init() {
    // Inp_init() function, inport init
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8);

    // Adc_init() function, A/D init
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_1);
    RCU_CFG0 |= (0b10 << 14) | (1 << 28);
    rcu_periph_clock_enable(RCU_ADC0);
    ADC_CTL1(ADC0) |= ADC_CTL1_ADCON;

    // Provided LCD init
    Lcd_Init();
}



/******************************************************************************
	   Welcome Page and related functions
******************************************************************************/

void show_str_dynamic(u16 x, u16 y, char str[], u16 color); // implemented in risc-v

// void show_str_dynamic(u16 x, u16 y, char str[], u16 color) {
//     char c = '\0';
//     int length = strlen(str);
//     for (int i = 0; i < length; i++) {
//         delay_1ms(50);
//         c = str[i];
//         LCD_ShowChar(x + i * 8, y, (u8) c, 1, color);
//     }
// }

void show_welcome_text(); // implemented in risc-v

// void show_welcome_text(){
//     LCD_Clear(BLACK);
//     show_str_dynamic(35, 15, "Chrome dino", BRED);
//     show_str_dynamic(30, 35, "Press any key", GBLUE);
//     show_str_dynamic(45, 55, "to play!", GBLUE);
// }

void welcome_page(){
    longan_led_init();
    RED_ON();
    GREEN_ON();
    BLUE_ON();

    BACK_COLOR = BLACK;

    show_welcome_text();
}

/******************************************************************************
	   Settings Page and related functions
******************************************************************************/

void print_select_mode(); // implemented in risc-v

// void print_select_mode(){
//     // clear the screen to be black
//     LCD_Clear(BLACK);

//     // draw the border
//     LCD_DrawRectangle(10, 5, 149, 75, WHITE);
    
//     // draw the scaffold framework
//     show_str_dynamic(35, 15, "Select Mode", WHITE);
//     show_str_dynamic(20, 40, "Debug", GREEN);
//     show_str_dynamic(70, 40, "Mid", YELLOW);
//     show_str_dynamic(110, 40, "Hard", MAGENTA);
    
//     // draw the underline
//     LCD_DrawLine(20, 56, 20+5*8, 56, WHITE);
//     LCD_DrawLine(70, 56, 70+3*8, 56, BLUE);
//     LCD_DrawLine(110, 56, 110+4*8, 56, BLUE);
// }

int settings_page(){
    BACK_COLOR = BLACK;

    int mode = 0;

    print_select_mode();

    int64_t time_stamp = get_timer_value();

    while (1){
        int boot0_pressed = Get_BOOT0();
        int btn0_pressed = Get_Button(0);
        if (boot0_pressed){
            return mode;
        }
        if (btn0_pressed && get_timer_value() - time_stamp > TIME_INTERVAL(250)){
            time_stamp = get_timer_value();
            switch (mode){
            case 0:
                mode = 1;
                LCD_DrawLine(20, 56, 20+5*8, 56, BLUE);
                LCD_DrawLine(70, 56, 70+3*8, 56, WHITE);
                break;
            case 1:
                mode = 2;
                LCD_DrawLine(70, 56, 70+3*8, 56, BLUE);
                LCD_DrawLine(110, 56, 110+4*8, 56, WHITE);
                break;
            case 2:
                mode = 0;
                LCD_DrawLine(110, 56, 110+4*8, 56, BLUE);
                LCD_DrawLine(20, 56, 20+5*8, 56, WHITE);
                break;
            }
        }
    }

    return mode;
}

/******************************************************************************
	   Functions to display pictures
******************************************************************************/

void my_lcd_show_black(u16 x1, u16 y1, u16 x2, u16 y2);  // implemented in risc-v

// void my_lcd_show_black(u16 x1, u16 y1, u16 x2, u16 y2) {
//     int size = (x2 - x1 + 1) * (y2 - y1 + 1) * 2;
//     LCD_Address_Set(x1, y1, x2, y2);
//     for (int i = 0; i < size; i++) {
//         LCD_WR_DATA8(0);
//     }
// }

void my_lcd_show_picture(u16 x1, u16 y1, u16 x2, u16 y2, unsigned char img[]);  // implemented in risc-v

// void my_lcd_show_picture(u16 x1, u16 y1, u16 x2, u16 y2, unsigned char img[]) {
//     int size = (x2 - x1 + 1) * (y2 - y1 + 1) * 2;
//     LCD_Address_Set(x1, y1, x2, y2);
//     for (int i = 0; i < size; i++) {
//         LCD_WR_DATA8(img[i]);
//     }
// }

void show_dino(u16 x, u16 y, u16 index) {
    my_lcd_show_picture(x, y, x + 19, y + 19, trex_arr[index]);
}


/******************************************************************************
	   Things related to the game
******************************************************************************/

#define NUM_GROUND_DOTS 15
#define NUM_OBSTACLES   1
#define NUM_BIRDS       1

/**
 * @brief The data structure for the game
 * 
 */
typedef struct Game_struct{
    // game status
    int64_t dino_body_index; // dinosour body shape
    int64_t jump_status;     // dino jump status
    int64_t score;           // score for the game

    struct { int64_t pos_x, pos_y;    } ground_dots[NUM_GROUND_DOTS]; // dots below the ground
    struct { int64_t pos_x; int64_t index;} obstacles[NUM_OBSTACLES]; // obstacles above the ground
    struct { int64_t pos_x, pos_y; int64_t index; } birds[NUM_BIRDS]; // birds in the air

    int64_t last_time_100;
    int64_t last_time_30 ;
    int64_t last_time_50 ;

    int16_t mode; // 0 -> debug, 1 -> mid, 2 -> hard

    int16_t super;
} Game;



/******************************************************************************
	   Functions related to the game
******************************************************************************/

/**
 * @brief Things to do before the game starts.
 * 
 * @param g The game struct to init on
 */
void game_init(Game* g){
    // init game status
    g->dino_body_index = 0;
    g->jump_status = 0;
    g->score = 0;
    g->super = 0;

    // draw the ground line
    LCD_DrawLine(0, 60, 160, 60, WHITE);

    // Init the dots below the ground
    for (int i = 0; i < NUM_GROUND_DOTS; i++) {
        g->ground_dots[i].pos_x = rand() % 170;
        g->ground_dots[i].pos_y = rand() % 6 + 62;
    }

    // Init the obstacles
    g->obstacles[0].pos_x = 320;
    g->obstacles[0].index = 0;
    // g->obstacles[1].pos_x = 480;
    // g->obstacles[1].index = 1;

    // Init the birds
    g->birds[0].pos_x = 400;
    g->birds[0].pos_y = 24;
    g->birds[0].index = 0;
    // g->birds[1].pos_x = 560;
    // g->birds[1].pos_y = 22;
    // g->birds[1].index = 1;
    
    // variables for time measurement use
    g->last_time_100 = get_timer_value();
    g->last_time_30  = get_timer_value();
    g->last_time_50  = get_timer_value();
}



#define FRAME_SPEED 2 // controls how fast the scene will move
#define SUPER_LENGTH 300 // controls how the super mode can last

/**
 * @brief Update the dots under the ground
 * 
 */
void update_frame_dots(Game* g){
    for (int i = 0; i < NUM_GROUND_DOTS; i++) {
        int ori_x = g->ground_dots[i].pos_x, ori_y = g->ground_dots[i].pos_y;
        // remove the previous dot
        LCD_DrawPoint(ori_x, ori_y, BLACK);  
        // move the dot left, or move it to the right if it hits the left border
        ori_x -= FRAME_SPEED;     
        if (ori_x < 0) ori_x = 160 + rand() % 15;
        // draw the new dot
        LCD_DrawPoint(ori_x, ori_y, WHITE);  // draw the new dot
        g->ground_dots[i].pos_x = ori_x;
    }
}

/**
 * @brief Update the obstacles (move them left), and check for collision
 * 
 * @return returns 1 if collide happens, 0 otherwise
 */
int update_frame_obstacles(Game* g){
    // update the obstacles
    int hit = 0;
    for (int i = 0; i < NUM_OBSTACLES; i++) {
        int ori_x = g->obstacles[i].pos_x;

        // beyond range, cannot display
        if (ori_x >= 148) {
            g->obstacles[i].pos_x -= FRAME_SPEED;
        }
        // if it is within the display range, display it
        else if (ori_x < 148 && ori_x > 10) {
            // clear the last frame (clear only the difference for better performance)
            my_lcd_show_black(ori_x - FRAME_SPEED + 11, 40, ori_x + 11, 59);
            // show the new frame
            my_lcd_show_picture(ori_x - FRAME_SPEED, 40, ori_x + 11 - FRAME_SPEED, 59, cactus_arr[g->obstacles[i].index]);
            g->obstacles[i].pos_x -= FRAME_SPEED;
            // check if collide happens
            if (ori_x >= 40 && ori_x <= 60 && g->jump_status <= 0) {
                hit = 1;
            }
        }
        // or, if it moves left out of bound, we just clear it
        else if (ori_x <= 10){
            // clear it
            my_lcd_show_black(0, 40, 22, 59);
            // move it to the right
            if (g->mode == 2){
                g->obstacles[i].pos_x = 160 + rand() % 10;
            } else {
                g->obstacles[i].pos_x = 160 * ((rand() % 3 >> 1) + 1);
            }
            // randomly switch its shape
            g->obstacles[i].index = rand() & 0b1;
        }
    }
    return hit;
}

/**
 * @brief Update the birds in the air, and check for collision
 * 
 * @return returns 1 if collide happens, 0 otherwise
 */
int update_frame_birds(Game* g) {
    // update the birds
    int bird_hit = 0;
    for (int i = 0; i < NUM_BIRDS; i++) {
        g->birds[i].index ++;
        int ori_x = g->birds[i].pos_x, ori_y = g->birds[i].pos_y;
        if (ori_x >= 140) {
            g->birds[i].pos_x -= FRAME_SPEED;
        } else if (ori_x < 140 && ori_x > 10) {
            my_lcd_show_black(ori_x - FRAME_SPEED + 19, ori_y, ori_x + 19, ori_y + 19);
            my_lcd_show_picture(ori_x - FRAME_SPEED, ori_y, ori_x + 19 - FRAME_SPEED, ori_y + 19, pter_arr[(g->birds[i].index) >> 2 & 0b1]);  // show the new frame
            g->birds[i].pos_x -= FRAME_SPEED;
            // check if hit
            if (ori_x >= 40 && ori_x <= 60 && g->jump_status != -1) {
                bird_hit = 1;
            }
        } else if (ori_x <= 10) {
            my_lcd_show_black(0, ori_y, 29, ori_y + 19);
            // g->birds[i].pos_x = 151 * (rand() % 3 + 2) + 10;
            if (g->mode == 2){  // hard mode (difficult)
                g->birds[i].pos_x = g->obstacles[i].pos_x + 70 + (rand() % 2) * 160;
            } else {
                g->birds[i].pos_x = g->obstacles[i].pos_x + 70 + (rand() % 3) * 160;
            }
        }
    }
    return bird_hit;
}

/**
 * @brief draw the super line indicator if the game is in super mode, 
 * clear the line otherwise
 * 
 * @return return 0 if in super mode, 1 if not in super mode  
 */
int update_frame_superline(Game* g){
    if (g->super == SUPER_LENGTH){
        LCD_Fill(60-1, 5, 60 + 50, 15, GREEN);
        return 0;
    } else if (g->super){
        LCD_Fill(g->super/6 + 59, 6, g->super/6 + 59, 14, BLACK);
        return 0;
    } else if (g->super == 0){
        LCD_Fill(60-1, 5, 60+50, 15, BLACK);  // clear the whole framework
        return 1;
    }
    return 1;
}

/**
 * @brief Update the frame and check for collision
 * 
 * @return 1 if collide happens, 0 otherwise
 */
int update_frame(Game* g){
    int collide = 0;
    update_frame_dots(g);
    collide |= update_frame_obstacles(g);
    collide |= update_frame_birds(g);
    collide &= update_frame_superline(g);
    if (g->super) g->super--;
    return collide;
}

void update_dino_body(Game* g){
    // update dinosour body
    g->dino_body_index++;
    int t = g->jump_status;
    if (t == -1){
        LCD_Fill(30, 15, 56, 59, BLACK);
        // my_lcd_show_black(30, 15, 56, 59);  // clear the air
        my_lcd_show_picture(30, 40, 56, 59, trex_arr[3 + (g->dino_body_index & 0b1)]);
    } else if (t == 0){
        show_dino(30, 40, (g->dino_body_index >> 2) & 0b1);
    } else if (t == 30){
        LCD_Fill(30, 15, 49, 59, BLACK);
        show_dino(30, 40, (g->dino_body_index >> 2) & 0b1);
        g->jump_status = 0;
    } else {
        LCD_Fill(30, 15, 49, 59, BLACK);
        // Use a quadratic functionto simulate the jump process 
        show_dino(30, 40 + (t-15) * (t-15) / 9 - (225/9), 2);
        g->jump_status ++;
    }
}



// start the game
void game_page(int mode){
    // clear the screen
    LCD_Clear(BLACK);

    // Init data structure for the game
    Game game_core;
    game_init(&game_core);
    game_core.mode = mode;

    while (1) {
        int64_t curr_time = get_timer_value();

        if (Get_Button(1)){  // check if creep button pressed
            game_core.jump_status = -1;
        } else if (game_core.jump_status == 0 && (Get_Button(0) || Get_BOOT0())){  // check if jump button pressed
            LCD_Fill(30, 40, 56, 59, BLACK);
            game_core.jump_status = 1;
        } else { // check if creep released
            if (game_core.jump_status == -1){
                LCD_Fill(30, 40, 56, 59, BLACK);
                game_core.jump_status = 0;
            }
        }

        #define SCORE_INTERVAL 100
        // update things with interval 100ms
        if (curr_time - game_core.last_time_100 > TIME_INTERVAL(SCORE_INTERVAL)) {
            game_core.last_time_100 = curr_time;

            // update score
            game_core.score++;
            if (game_core.score >= 299 && game_core.score % 300 >= 0 && game_core.score % 300 <= 10){
                // blink the score, and show the score in green color
                if (game_core.score & 0b1) LCD_ShowNum(110, 5, game_core.score, 5, GREEN);
                else LCD_ShowString(110, 5, (u8*)"     ", GREEN);
                if (game_core.super == 0){
                    game_core.super = SUPER_LENGTH;
                }
            } else {
                LCD_ShowNum(110, 5, game_core.score, 5, WHITE);
            }
        }

        #define DINO_INTERVAL 30
        if (curr_time - game_core.last_time_50 > TIME_INTERVAL(DINO_INTERVAL)) {
            game_core.last_time_50 = curr_time;
            update_dino_body(&game_core);  // update dinosour body
        }

        #define FRAME_INTERVAL 30
        // update things with interval 50ms
        if (curr_time - game_core.last_time_30 > TIME_INTERVAL(FRAME_INTERVAL)) {
            game_core.last_time_30 = curr_time;
            int hit_flag = update_frame(&game_core);
            if (mode == 0){
                if (hit_flag){
                    LCD_ShowString(100, 20, (u8*)"Fail", RED);
                } else {
                    LCD_ShowString(100, 20, (u8*)"Safe", GREEN);
                }
            } else if (mode == 1 || mode == 2) {
                if (hit_flag){
                    // Show game over window
                    LCD_Fill(20, 20, 140, 60, GRAYBLUE);
                    LCD_DrawRectangle(20, 20, 140, 60, WHITE);
                    BACK_COLOR = GRAYBLUE;
                    LCD_ShowString(43, 30, (u8*) "Game Over", WHITE);
                    BACK_COLOR = BLACK;
                    delay_1ms(1000);  // avoid misoperation
                    return;
                }
            }
        }
    }
}

int main();  // implemented in risc-v

/*
int main() {
    IO_init();   // miscellaneous initialize

    welcome_page();  // display the welcome page

    while (!Get_BOOT0() && !Get_Button(0) && !Get_Button(1)) delay_1ms(10);  // wait until BOOT0 button pressed

    while (1){
        int mode = settings_page();  // a simple settings menu
        game_page(mode);  // game page
        while (!Get_BOOT0() && !Get_Button(0) && !Get_Button(1)) delay_1ms(10);  // wait until BOOT0 button pressed
    }

    return 0;
}
*/
