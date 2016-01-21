#include "Utils.h"
#include <math.h>


const double Utils::Pi = 3.141592653589793238463;

unsigned Utils::window_x = 600;
unsigned Utils::window_y = 400;

int Utils::line_w = round(0.0066 * window_x);
int Utils::left_wall_d = line_w * 2;
int Utils::right_wall_d = window_x - line_w;
int Utils::top_wall_d = line_w;

int Utils::racquet_x = round(0.117 * window_x); 
int Utils::racquet_y = round(0.0175 * window_y);
int Utils::catchline_y = round(0.875 * window_y);

int Utils::ball_r = round(0.025 * window_y);
int Utils::ball_start_height = round(0.2 * window_y);
double Utils::ball_speed = round(0.01 * window_y);;
double Utils::ball_angle = 1.6 * Pi;

int Utils::nozone_top = top_wall_d + line_w + ball_r;
int Utils::nozone_left = left_wall_d + line_w + ball_r;
int Utils::nozone_right = right_wall_d - line_w - ball_r;
int Utils::nozone_catchline = catchline_y - racquet_y / 2 - ball_r;
