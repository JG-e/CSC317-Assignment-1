#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  int len = height*width;
  gray.resize(len);
  ////////////////////////////////////////////////////////////////////////////
  /* 
  Take the rgb and for every pixel calculate the grayness of the gray using the 
  following formulae:
  greyness = 0.2126r + 0.7152g + 0.0722b 
  Assuming rgb and gray have the same dimensions in pixels
  */ 
  for (int i = 0; i < len; i++) {
    gray[i] = 0.2126 * rgb[i] + 0.7152 * rgb[i+1] + 0.0722 * rgb[i+2];
  }
  ////////////////////////////////////////////////////////////////////////////
}


