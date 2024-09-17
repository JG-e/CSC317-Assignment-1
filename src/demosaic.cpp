#include "demosaic.h"
std::vector<int> get_neighbours(int index, int width, int height);
void increment_and_plus(int& num, int& val, std::vector<int> increment_vals);
void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  /*
  for each pixel, we'll use the exact color sample when it's available and 
  average available neighbors (in all 8 directions) to fill in missing colors.
  */ 
  unsigned int rgb_flag; // 0 as red, 1 as green, 2 as blue
  int r_val;
  int g_val; 
  int b_val;
  int num_r; 
  int num_g;
  int num_b;

  // For each pixel
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int pixel = x + y * height;
    // if I have the exact value, take it (Say I am on a green valued grayscale pixel)
    if (y % 2 == 0) {
      if (x % 2 == 0) { 
        rgb_flag = 1;
        g_val = bayer[pixel];
      }
      else {
        rgb_flag = 2;
        b_val = bayer[pixel];
      }
    }
    else {
      if (x % 2 == 0) {
        rgb_flag = 0;
        r_val = bayer[pixel];
      }
      else {
        rgb_flag = 1;
        g_val = bayer[pixel];
      }
    } 
    // Then take the average of the neighbours' R and B values (Take from R neighbours
    // if calculating R, and vice versa).
    std::vector<int> neighbours = get_neighbours(pixel, width, height);

    switch (rgb_flag) {
      case 0: 
        // Red case: Left, right, up, down are green, the 4 corners are blue
        increment_and_plus(num_g, g_val, {3, 4, 1, 6});
        increment_and_plus(num_b, b_val, {0, 2, 5, 7});
        g_val /= num_g; 
        b_val /= num_b;
        break;
      case 1: 
        // Green case: odd row: up down are red. left right are blue. even row: 
        // up down are blue. Left right are red. 
        increment_and_plus(num_r, r_val, {1, 6});
        increment_and_plus(num_b, b_val, {3, 4});
        r_val /= num_r; 
        b_val /= num_b;
        break;
      case 2:
        // Blue case: up down left right are green, corners are red
        increment_and_plus(num_g, g_val, {3, 4, 1, 6});
        increment_and_plus(num_r, r_val, {0, 2, 5, 7});
        break;
        g_val /= num_g;
        num_r /= r_val;
    }

    // Assign the recovered rgb values back to rgb
    int rgb_pixel = pixel * 3;
    rgb[rgb_pixel] = r_val;
    rgb[rgb_pixel + 1] = g_val; 
    rgb[rgb_pixel + 2] = b_val;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

std::vector<int> get_neighbours(int index, int width, int height) {
  std::vector<int> neighbors;
    
    // Convert 1D index to 2D coordinates (row, col)
    int row = index / width;
    int col = index % width;

    // Directions representing the 8 neighbors (row_offset, col_offset)
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},  // Top-left, Top, Top-right
        { 0, -1},          { 0, 1},  // Left,       Right
        { 1, -1}, { 1, 0}, { 1, 1}   // Bottom-left, Bottom, Bottom-right
    };
    int neighborIndex;
    // Iterate through each direction
    for (int i = 0; i < 8; ++i) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];

        // Check if the new position is within bounds
        if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width) {
            neighborIndex = newRow * width + newCol;
        } 
        else {
          neighborIndex = -1;
        }
        neighbors.push_back(neighborIndex);

    }

    return neighbors;
}

void increment_and_plus(int& num, int& val, std::vector<int> increment_vals) { 
  for (int v: increment_vals) {
    if (v > -1) {
      num++;
      val += v;
    }
  }
}