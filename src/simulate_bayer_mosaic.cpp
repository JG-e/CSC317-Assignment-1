#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  ////////////////////////////////////////////////////////////////////////////
  /*
  This bayer mosaic turns a regular rgb to mosaic by taking the intensity of the 
  interleaving order of the rgb values. The order is Green, Blue, Green, Blue ...
  for the odd row, and Red, Green, Red, Green, ... for the even row
  */

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int curr_i = (i * width + j);
      int rgb_i = curr_i * 3;
    // If row # is even, then go with GBGB...
      if (i % 2 == 0) {
        bayer[curr_i] = j % 2 == 0 ? rgb[rgb_i + 1] : rgb[rgb_i + 2];
      }
    // If row # is odd, then RGRG...
      else {
        bayer[curr_i] = j % 2 == 0 ? rgb[rgb_i] : rgb [rgb_i + 1];
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
