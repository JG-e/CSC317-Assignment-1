#include "hsv_to_rgb.h"
#include <cmath>
using namespace std; 
void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  ////////////////////////////////////////////////////////////////////////////
  
  r = 0;
  g = 0;
  b = 0;

  double M = v; 
  double C = s * v; 
  double hp = h / 60; 
  double x = C * (1.0 - abs(fmod(hp, 2.0) - 1.0)); // X = C * (1 - \H' % 2 - 1\)
    if (0 <= hp && hp < 1) {
	  r = C;
	  g = x;
	  b = 0;
  }
  else if (1 <= hp && hp < 2) {
	  r = x;
	  g = C;
	  b = 0;
  }
  else if (2 <= hp && hp < 3) {
	  r = 0;
	  g = C;
	  b = x;
  }
  else if (3 <= hp && hp < 4) {
	  r = 0;
	  g = x;
	  b = C;
  }
  else if (4 <= hp && hp < 5) {
	  r = x;
	  g = 0;
	  b = C;
  }
  else if (5 <= hp && hp < 6) {
	  r = C;
	  g = 0;
	  b = x;
  }

  double m = v - C;
  r = 255.0 * (r + m);
  g = 255.0 * (g + m);
  b = 255.0 * (b + m);
  return;
  ////////////////////////////////////////////////////////////////////////////
}
