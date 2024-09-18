#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

unsigned char _cast_rgb2(double val);

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  double h, s, v, r, g, b;
  for (int i = 0; i < width * height * 3; i+=3) {
    rgb_to_hsv(rgb[i] / 255.0, rgb[i+1] / 255.0, rgb[i+2] / 255.0, h, s, v);
    s *= 1 - factor;
    hsv_to_rgb(h, s, v, r, g, b); 
    desaturated[i] = _cast_rgb2(r); 
    desaturated[i+1] = _cast_rgb2(g);
    desaturated[i+2] = _cast_rgb2(b);
  }
  ////////////////////////////////////////////////////////////////////////////
}


unsigned char _cast_rgb2(double val) {
  return static_cast<unsigned char>(val * 255);
}
