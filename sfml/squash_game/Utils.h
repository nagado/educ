#ifndef UTILS_H
#define UTILS_H

#include <math.h>


namespace Utils
{
  const double Pi = 3.141592653589793238463;

  const unsigned window_x = 600;
  const unsigned window_y = 400;

  const int line_w = round(0.0066 * window_x);
  const int left_wall_d = line_w * 2;
  const int right_wall_d = window_x - line_w;
  const int top_wall_d = line_w;

  const int racquet_x = round(0.117 * window_x);
  const int racquet_y = round(0.0175 * window_y);
  const int catchline_y = round(0.875 * window_y);

  const int ball_r = round(0.025 * window_y);
  const int ball_start_height = round(0.2 * window_y);
  const double ball_speed = round(0.01 * window_y);
  const double ball_angle = 1.6 * Pi;

  const int nozone_top = top_wall_d + line_w + ball_r;
  const int nozone_left = left_wall_d + line_w + ball_r;
  const int nozone_right = right_wall_d - line_w - ball_r;
  const int nozone_catchline = catchline_y - racquet_y / 2 - ball_r;
}

#endif
