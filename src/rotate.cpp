#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  /* 
  Turn every row into every column: row 1's pixels becomes column 1's 
  pixels starting from the bottom, row 2's pixels become column 2's 
  pixels starting from the bottom, etc.
  */
  int len = width * height;
  // Track the current pixel of input and rotated
  int curr_row = 0;
  int curr_input; 
  int curr_rotate;
  // Put the RGB or greyscale value in the rotated 
  for (int i = 0; i < len; i++) {
    // Increment input and rotated pixel by number of pixels
    curr_input = i * num_channels; 
    curr_rotate = (height * (width - 1 - i) + curr_row) * num_channels;
    for (int channel = 0; channel < num_channels; channel++) {
      // Copy every pixels' channel value
      rotated[curr_rotate + channel] = input[curr_input + channel];
    }
    // Once reaches the end of the row, update the row
    if (i > 0 && (i % width) == 0) { 
      curr_row++;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
