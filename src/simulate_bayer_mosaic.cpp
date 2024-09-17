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

  // Keep track of the row 
  int curr_row = 1;
  int len = width * height;
  for (int i = 0; i < len; i++) {
  // If row # is odd, then go with GBGB...
    if (curr_row % 2 == 1) {
      bayer[i] = i % 2 == 0 ? rgb[i * 3 + 1] : rgb[i * 3 + 2];
    }
  // If row # is even, then RGRG...
    else {
      bayer[i] = i % 2 == 0 ? rgb[i * 3] : rgb [i * 3 + 1];
    }
  // Increment row if i is multiple of width
    if (i > 0 && (i % width) == 0)  
      curr_row++;
  }
  ////////////////////////////////////////////////////////////////////////////
}
