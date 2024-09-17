#include "rgb_to_hsv.h"
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;
void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  ////////////////////////////////////////////////////////////////////////////
  double M = max({r,g,b});
  double m = min({r,g,b});
  double C = M - m; 

  double hp; 

  if (C == 0)
    hp = -1; // not defined
  else if (M == r)
    hp = fmod((g-b)/C, 6);
  else if (M == g)
    hp = (b-r) / C + 2; 
  else if (M == b) 
    hp = (r-g) / C + 4;
  
  h = 60 * hp;
  v = M;
  s = v == 0 ? 0 : C / v;
  
  ////////////////////////////////////////////////////////////////////////////
}
