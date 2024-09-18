#include "over.h"

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  ////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < width * height * 4; i += 4) {
    // For each pixel in A and B, apply 
    const int r1 = +A[i];
    const int g1 = +A[i+1];
    const int b1 = +A[i+2];
    const int alpha1 = +A[i+3];

    const int r2 = +B[i];
    const int g2 = +B[i+1];
    const int b2 = +B[i+2];
    const int alpha2 = +B[i+3];

    const double a1 = (double)alpha1 / 255;
    const double a2 = (double)alpha2 / 255;
    const double a0 = a1 + a2 * (1 - a1);

    C[i] = (r1 * a1 + r2 * a2 * (1 - a1)) / a0;
    C[i+1] = (g1 * a1 + g2 * a2 * (1 - a1)) / a0;
    C[i+2] = (b1 * a1 + b2 * a2 * (1 - a1)) / a0;
    C[i+3] = (unsigned char)(a0 * 255);
  }
  ////////////////////////////////////////////////////////////////////////////
}
