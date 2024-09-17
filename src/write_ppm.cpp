#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  using namespace std;
  unsigned char p2orp3 = (num_channels == 3) ? 0 : 1; // a flag showing if p2 or p3, 0 as p3, 1 as p2;
  int len = width * height;
  ofstream f; 
  f.open(filename);
  if (!f.is_open()) { 
    return false;
  }
  // Write header number according to the file format
  if (!p2orp3) {
    f << "P3" << endl;
  } 
  else { 
    f << "P2" << endl;
  }
  // width and height according to the protocol
  f << width << ' ' << height << endl;
  // set up max value
  f << 255 << endl; 
  for (int i = 0; i < len; i++) {
    if (!p2orp3){
      int j = i*3;
      f << +(data[j]) << ' ' << +data[j+1] << ' ' << +data[j+2] << ' ';
      // f << +(data[j]) << ' ' << +data[j+1] << ' ' << +data[j+2] << endl;
    }
    else{ 
      f << +data[i] << endl;
      }
    if (i > 0 && i % width == 0)
      f << endl;
  }
  f.close();
  return true;
}
