#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

unsigned char cast_rgb(double val); 

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  double h, s, v, r, g, b;
  for (int i = 0; i < width * height * 3; i+=3) {
    rgb_to_hsv(rgb[i], rgb[i+1], rgb[i+2], h, s, v);
    h = abs(fmod(h + shift, 360));
    hsv_to_rgb(h, s, v, r, g, b); 
    shifted[i] = cast_rgb(r); 
    shifted[i+1] = cast_rgb(g);
    shifted[i+2] = cast_rgb(b);
  }
  ////////////////////////////////////////////////////////////////////////////
}

unsigned char cast_rgb(double val) {
  return (unsigned char) (val * 255);
}