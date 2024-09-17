#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  int pixel_start; // The start index of the current pixel
  int reverse_start; // The start index of the reversed image's pixel
  ////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
    /* 
    Read every pixel at a row of the original image and 
    put in the same row of the reflected image in the reversed order.
    */ 
    pixel_start = (i * width + j) * num_channels;
    reverse_start = ((i + 1) * width - j) * num_channels;
      for (int k = 0; k < num_channels; k++) {
        reflected[reverse_start + k] = input[pixel_start + k]; 
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
