/* This files provides address values that exist in the system */
#define SDRAM_BASE            0xC0000000
#define FPGA_ONCHIP_BASE      0xC8000000
#define FPGA_CHAR_BASE        0xC9000000

/* Cyclone V FPGA devices */
#define LEDR_BASE             0xFF200000
#define HEX3_HEX0_BASE        0xFF200020
#define HEX5_HEX4_BASE        0xFF200030
#define SW_BASE               0xFF200040
#define KEY_BASE              0xFF200050
#define TIMER_BASE            0xFF202000
#define PIXEL_BUF_CTRL_BASE   0xFF203020
#define CHAR_BUF_CTRL_BASE    0xFF203030

/* VGA colors */
#define WHITE 0xFFFF
#define YELLOW 0xFFE0
#define RED 0xF800
#define GREEN 0x07E0
#define BLUE 0x001F
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define GREY 0xC618
#define PINK 0xFC18
#define ORANGE 0xFC00
#define BLACK 0x0000

#define ABS(x) (((x) > 0) ? (x) : -(x))

/* Screen size. */
#define RESOLUTION_X 320
#define RESOLUTION_Y 240

/* Constants for animation */
#define BOX_LEN 2
#define NUM_BOXES 8

#define FALSE 0
#define TRUE 1

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// Begin part3.c code for Lab 7
volatile int pixel_buffer_start; // global variable

// Funciton Decleration
void wait_for_vsync();
void clear_screen();
void swap(int *xp, int *yp);
void draw_line(int x0, int y0, int x1, int y1, short int line_color);
void draw_box(int x0, int y0, short int box_color);
void plot_pixel(int x, int y, short int line_color);

// A 2D Array That Store All The Cell
int Cell_Array[RESOLUTION_Y][RESOLUTION_X] = {0};


int main(void)
{
    // Variable Declaration
    srand(time(NULL));

    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    // declare other variables(not shown)
    // initialize location and direction of rectangles(not shown)

    /* set front pixel buffer to start of FPGA On-chip memory */
    *(pixel_ctrl_ptr + 1) = 0xC8000000; // first store the address in the 
                                        // back buffer
    /* now, swap the front/back buffers, to set the front buffer location */
    wait_for_vsync();
    /* initialize a pointer to the pixel buffer, used by drawing functions */
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen(); // pixel_buffer_start points to the pixel buffer
    /* set back pixel buffer to start of SDRAM memory */
    *(pixel_ctrl_ptr + 1) = 0xC0000000;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // we draw on the back buffer
    clear_screen(); // pixel_buffer_start points to the pixel buffer

    // Initializing The Life Game (Version 1)
    /* Cell_Array[0][1] = 1;
    Cell_Array[1][2] = 1;
    Cell_Array[2][0] = 1;
    Cell_Array[2][1] = 1;
    Cell_Array[2][2] = 1; */

    // Initializing The Life Game (Version 1)
    Cell_Array[20][20] = 1;
    Cell_Array[21][20] = 1;

    Cell_Array[20][21] = 1;
    Cell_Array[21][21] = 1;

    Cell_Array[20][25] = 1;

    Cell_Array[19][26] = 1;
    Cell_Array[20][26] = 1;
    Cell_Array[21][26] = 1;

    Cell_Array[18][27] = 1;
    Cell_Array[22][27] = 1;

    Cell_Array[17][28] = 1;
    Cell_Array[19][28] = 1;
    Cell_Array[20][28] = 1;
    Cell_Array[21][28] = 1;
    Cell_Array[23][28] = 1;

    Cell_Array[18][29] = 1;
    Cell_Array[19][29] = 1;
    Cell_Array[20][29] = 1;
    Cell_Array[21][29] = 1;
    Cell_Array[22][29] = 1;

    Cell_Array[21][43] = 1;
    Cell_Array[22][43] = 1;
    Cell_Array[23][43] = 1;

    Cell_Array[20][44] = 1;
    Cell_Array[24][44] = 1;

    Cell_Array[19][45] = 1;
    Cell_Array[25][45] = 1;

    Cell_Array[19][46] = 1;
    Cell_Array[20][46] = 1;
    Cell_Array[22][46] = 1;
    Cell_Array[24][46] = 1;
    Cell_Array[25][46] = 1;

    Cell_Array[22][49] = 1;

    Cell_Array[21][50] = 1;
    Cell_Array[23][50] = 1;

    Cell_Array[21][51] = 1;
    Cell_Array[23][51] = 1;

    Cell_Array[22][52] = 1;

    Cell_Array[22][54] = 1;
    Cell_Array[23][54] = 1;
    Cell_Array[22][55] = 1;
    Cell_Array[23][55] = 1;

    while (1)
    {   
        // Draw The VGA Display
        for (int row_num = 0; row_num < RESOLUTION_Y; row_num++){
            for (int col_num = 0; col_num < RESOLUTION_X; col_num++){
                if (Cell_Array[row_num][col_num] == 1) plot_pixel(col_num, row_num, WHITE);
                else plot_pixel(col_num, row_num, BLACK);
            }
        }
        
        // An Array To Store New Cells
        int New_Cell_Array[RESOLUTION_Y][RESOLUTION_X] = {0};

        // Top Left Corner
        if (Cell_Array[0][1] == 1 && Cell_Array[1][0] == 1 && Cell_Array[1][1] == 1 && Cell_Array[0][0] == 0) New_Cell_Array[0][0] == 1;

        // Top Right Corner
        if (Cell_Array[0][RESOLUTION_X - 2] == 1 && Cell_Array[1][RESOLUTION_X - 1] == 1 && Cell_Array[1][RESOLUTION_X - 2] == 1 && Cell_Array[0][RESOLUTION_X - 1] == 0) New_Cell_Array[0][RESOLUTION_X - 1] == 1;

        // Bottom Left Corner
        if (Cell_Array[RESOLUTION_Y - 1][1] == 1 && Cell_Array[RESOLUTION_Y - 2][0] == 1 && Cell_Array[RESOLUTION_Y - 2][1] == 1 && Cell_Array[RESOLUTION_Y - 1][0] == 0) New_Cell_Array[RESOLUTION_Y - 1][0] == 1;

        // Bottom Right Corner
        if (Cell_Array[RESOLUTION_Y - 1][RESOLUTION_X - 2] == 1 && Cell_Array[RESOLUTION_Y - 2][RESOLUTION_X - 1] == 1 && Cell_Array[RESOLUTION_Y - 2][RESOLUTION_X - 2] == 1 && Cell_Array[RESOLUTION_Y - 1][RESOLUTION_X - 1] == 0) New_Cell_Array[RESOLUTION_Y - 1][RESOLUTION_X - 1] == 1;

        // Upper Row and Bottom Row
        for (int col_num = 1; col_num < RESOLUTION_X - 1; col_num++){
            // Upper Row
            int count = 0;
            if (Cell_Array[0][col_num - 1] == 1) count++;
            if (Cell_Array[0][col_num + 1] == 1) count++;
            if (Cell_Array[1][col_num - 1] == 1) count++;
            if (Cell_Array[1][col_num] == 1) count++;
            if (Cell_Array[1][col_num + 1] == 1) count++;

            if (Cell_Array[0][col_num] == 1) {
                if (count != 2 && count != 3) New_Cell_Array[0][col_num] = 0;
                else New_Cell_Array[0][col_num] = 1;
            } else {
                if (count == 3) New_Cell_Array[0][col_num] = 1;
            }
            
            // Bottom Row
            count = 0;
            if (Cell_Array[RESOLUTION_Y - 1][col_num - 1] == 1) count++;
            if (Cell_Array[RESOLUTION_Y - 1][col_num + 1] == 1) count++;
            if (Cell_Array[RESOLUTION_Y - 2][col_num - 1] == 1) count++;
            if (Cell_Array[RESOLUTION_Y - 2][col_num] == 1) count++;
            if (Cell_Array[RESOLUTION_Y - 2][col_num + 1] == 1) count++;

            if (Cell_Array[RESOLUTION_Y - 1][col_num] == 1) {
                if (count != 2 && count != 3) New_Cell_Array[RESOLUTION_Y - 1][col_num] = 0;
                else New_Cell_Array[RESOLUTION_Y - 1][col_num] = 1;
            } else {
                if (count == 3) New_Cell_Array[RESOLUTION_Y - 1][col_num] = 1;
            }
        }
        
        // Left Most and Right Most Column
        for (int row_num = 1; row_num < RESOLUTION_Y - 1; row_num++){
            // Left Most Column
            int count = 0;
            if (Cell_Array[row_num - 1][0] == 1) count++;
            if (Cell_Array[row_num + 1][0] == 1) count++;
            if (Cell_Array[row_num - 1][1] == 1) count++;
            if (Cell_Array[row_num][1] == 1) count++;
            if (Cell_Array[row_num + 1][1] == 1) count++;

            if (Cell_Array[row_num][0] == 1) {
                if (count != 2 && count != 3) New_Cell_Array[row_num][0] = 0;
                else New_Cell_Array[row_num][0] = 1;
            } else {
                if (count == 3) New_Cell_Array[row_num][0] = 1;
            }

            // Right Most Column
            count = 0;
            if (Cell_Array[row_num - 1][RESOLUTION_X - 1] == 1) count++;
            if (Cell_Array[row_num + 1][RESOLUTION_X - 1] == 1) count++;
            if (Cell_Array[row_num - 1][RESOLUTION_X - 2] == 1) count++;
            if (Cell_Array[row_num][RESOLUTION_X - 2] == 1) count++;
            if (Cell_Array[row_num + 1][RESOLUTION_X - 2] == 1) count++;

            if (Cell_Array[row_num][RESOLUTION_X - 1] == 1) {
                if (count != 2 && count != 3) New_Cell_Array[row_num][RESOLUTION_X - 1] = 0;
                else New_Cell_Array[row_num][RESOLUTION_X - 1] = 1;
            } else {
                if (count == 3) New_Cell_Array[row_num][RESOLUTION_X - 1] = 1;
            }
        }

        // Check Middle Cells
        for (int row_num = 1; row_num < RESOLUTION_Y - 1; row_num++){
            for (int col_num = 1; col_num < RESOLUTION_X - 1; col_num++){
                // All Other Places
                int count = 0;
                if (Cell_Array[row_num - 1][col_num - 1] == 1) count++;
                if (Cell_Array[row_num - 1][col_num] == 1) count++;
                if (Cell_Array[row_num - 1][col_num + 1] == 1) count++;
                if (Cell_Array[row_num][col_num - 1] == 1) count++;
                if (Cell_Array[row_num][col_num + 1] == 1) count++;
                if (Cell_Array[row_num + 1][col_num - 1] == 1) count++;
                if (Cell_Array[row_num + 1][col_num] == 1) count++;
                if (Cell_Array[row_num + 1][col_num + 1] == 1) count++;

                if (Cell_Array[row_num][col_num] == 1) {
                    if (count != 2 && count != 3) New_Cell_Array[row_num][col_num] = 0;
                    else New_Cell_Array[row_num][col_num] = 1;
                } else {
                    if (count == 3) New_Cell_Array[row_num][col_num] = 1;
                }
            }
        }

        // Replace With New Cells
        for (int row_num = 0; row_num < RESOLUTION_Y; row_num++){
            for (int col_num = 0; col_num < RESOLUTION_X; col_num++){
                Cell_Array[row_num][col_num] = New_Cell_Array[row_num][col_num];
            }
        }

        wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
    }
}

// Function For Waiting Vertical Sychronization
void wait_for_vsync(){
    volatile int * pixel_ctrl_ptr = (int *) 0xFF203020;
    volatile int * pixel_status_register = (int *)0xFF20302C;

    * pixel_ctrl_ptr = 1;
    int status = *pixel_status_register;
    // Wait Until The S Bit In The Status Register Turns Into Zero
    while ((status & 0x00000001) != 0){
        status = *pixel_status_register;
    }
}

// code not shown for clear_screen() and draw_line() subroutines
// Function For Clearing The Entire Screen
void clear_screen(){
	int row_num, col_num;
    for (row_num = 0; row_num < RESOLUTION_Y; row_num++){
        for (col_num = 0; col_num < RESOLUTION_X; col_num++){
            plot_pixel(col_num, row_num, BLACK);
        }
    }
}

// Helper Function For Swapping Two Integer Variables
void swap(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function For Drawing A Straight Line Using Bresenham's Algorithm
void draw_line(int x0, int y0, int x1, int y1, short int line_color){
    bool is_steep = abs(y1 - y0) > abs(x1 - x0);
    if (is_steep){
        swap(&x0, &y0);
        swap(&x1, &y1);
    }
    if (x0 > x1){
        swap(&x0, &x1);
        swap(&y0, &y1);
    }

    // Variable Decleration
    int deltax = x1 - x0;
    int deltay = abs(y1 - y0);
    int error = -(deltax / 2);
    int y = y0;
    int y_step;
    
    // Determine Positive Or Negative Y Increment
    if (y0 < y1) y_step = 1;
    else y_step = -1;
	
	int x;
    for (x = x0; x < x1; x++){
        if (is_steep) plot_pixel(y, x, line_color);
        else plot_pixel(x, y, line_color);

        // Determining Increment Y Or Not
        error = error + deltay;
        if (error > 0){
            y = y + y_step;
            error = error - deltax;
        }
    }
}

// Function For Drawing Line
void draw_box(int x0, int y0, short int box_color){
	int row_num, col_num;
    for (row_num = -1; row_num <= 1; row_num++){
        for (col_num = -1; col_num <= 1; col_num++){
            plot_pixel(x0 + col_num, y0 + row_num, box_color);
        }
    }
}

// Function Used For Drawing A Single Pixel On the Screen
void plot_pixel(int x, int y, short int line_color){
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}
