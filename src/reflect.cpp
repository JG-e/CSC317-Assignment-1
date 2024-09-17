#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  int len = width * height;
  reflected.resize(width*height*num_channels);
  int pixel_start; // The start index of the current pixel
  int reverse_start; // The start index of the reversed image's pixel
  int curr_row = 1;
  ////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < len; i++) {
    /* 
    Read every pixel at a row of the original image and 
    put in the same row of the reflected image in the reversed order.
    */ 
    pixel_start = i * num_channels;
    reverse_start = curr_row * width - (i % width);
    for (int j = 0; j < num_channels; j++) {
      reflected[reverse_start + j] = input[pixel_start + j]; 
    }
    // Increment row when it hits multiple of width
    if ((i % width) == 0)
      curr_row++;
  }
  ////////////////////////////////////////////////////////////////////////////
}
