#include "demosaic.h"
std::vector<int> get_neighbours(int index, int width, int height);

void increment_and_plus(
  int& num, 
  int& val, 
  std::vector<int> neighbour_indices, 
  std::vector<int> neighbours,
  const std::vector<unsigned char> & bayer
  );
  
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
      // Initialize these values for every pixel 
      num_r = 0; 
      num_g = 0;
      num_b = 0; 
      r_val = 0; 
      g_val = 0; 
      b_val = 0;
      int curr_pixel_i = y * width + x;
      // if I have the exact value, take it 
      // (Say I am on a green valued grayscale pixel, I'll use the green value)
      if (y % 2 == 0) {
        // Even index row is GBGB...
        if (x % 2 == 0) { 
          // GBGB starts with G
          rgb_flag = 1;
          num_g++;
          g_val = bayer[curr_pixel_i];
        }
        else {
          // GBGB is then B
          rgb_flag = 2;
          num_b++;
          b_val = bayer[curr_pixel_i];
        }
      }
      else {
        // Odd index rows are RGRG
        if (x % 2 == 0) {
          // Starts with a R
          rgb_flag = 0;
          num_r++;
          r_val = bayer[curr_pixel_i];
        }
        else {
          // Then with a G
          rgb_flag = 1;
          num_g++;
          g_val = bayer[curr_pixel_i];
        }
      } 
      // Then take the average of the neighbours' R and B values (Take from R neighbours
      // if calculating R, and vice versa).
      std::vector<int> neighbours = get_neighbours(curr_pixel_i, width, height);

      switch (rgb_flag) {
        case 0: 
          // Red case: Left, right, up, down are green, the 4 corners are blue
          increment_and_plus(num_g, g_val, {3, 4, 1, 6}, neighbours, bayer);
          increment_and_plus(num_b, b_val, {0, 2, 5, 7}, neighbours, bayer);
          break;
        case 1: 
          // Green case: even index row: up down are red. left right are blue. 
          if (y % 2 == 0) {
            increment_and_plus(num_r, r_val, {1, 6}, neighbours, bayer);
            increment_and_plus(num_b, b_val, {3, 4}, neighbours, bayer);
            // increment_and_plus(num_g, g_val, {0, 2, 5, 7}, neighbours, bayer);
          }
          // Odd index row: up down are blue. Left right are red. The 4 corners are green.
          else {
            increment_and_plus(num_r, r_val, {3, 4}, neighbours, bayer);
            increment_and_plus(num_b, b_val, {1, 6}, neighbours, bayer);
            // increment_and_plus(num_g, g_val, {0, 2, 5, 7}, neighbours, bayer);
          }
          break;
        case 2:
          // Blue case: up down left right are green, corners are red
          increment_and_plus(num_g, g_val, {3, 4, 1, 6}, neighbours, bayer);
          increment_and_plus(num_r, r_val, {0, 2, 5, 7}, neighbours, bayer);
          break;
      }
      r_val /= num_r; 
      b_val /= num_b;
      g_val /= num_g;
      // Assign the recovered rgb values back to rgb
      int rgb_pixel = curr_pixel_i * 3;
      rgb[rgb_pixel] = num_r == 0 ? 0 : static_cast<unsigned char>(r_val);
      rgb[rgb_pixel + 1] = num_g == 0 ? 0 : static_cast<unsigned char>(g_val); 
      rgb[rgb_pixel + 2] = num_b == 0 ? 0 : static_cast<unsigned char>(b_val);
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

void increment_and_plus(
  int& num, 
  int& val, 
  std::vector<int> neighbour_indices, 
  std::vector<int> neighbours,
  const std::vector<unsigned char> & bayer
  ) { 
  for (int i: neighbour_indices) {
      int bayer_i = neighbours[i];
      if (bayer_i == -1)
        continue;
      int v = bayer[bayer_i];
      num++;
      val += v;
  }
}