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
  int curr_input; 
  int curr_rotate;
  // Put the RGB or greyscale value in the rotated 
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // Increment input and rotated pixel by number of pixels
      curr_input = (i * width + j) * num_channels; 
      curr_rotate = (height * (width - j - 1) + i) * num_channels;
      for (int channel = 0; channel < num_channels; channel++) {
        // Copy every pixels' channel value
        rotated[curr_rotate + channel] = input[curr_input + channel];
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
