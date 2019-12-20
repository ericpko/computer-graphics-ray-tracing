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
  ////////////////////////////////////////////////////////////////////////////
    assert(
    (num_channels == 3 || num_channels == 1 ) &&
    ".ppm only supports RGB or grayscale images");

  // Check the dimensions of the image
  if (width == 0 || height == 0) {
    std::cerr << "Check dimensions of image" << std::endl;
    // std::perror("Check dimensions of image"); // no error number generated
    return false;
  }

  // Create an output file stream object
  std::ofstream ofs;  // output file stream (ofs)
  ofs.open(filename, std::ios::binary | std::ios::out | std::ios::trunc);

  if (ofs.fail()) {
    std::perror("open");
    // std::cerr << "Problem opening file to write: " << strerror(errno) << std::endl;
    // throw("Problem opening file");
    exit(EXIT_FAILURE);

  } else if (!ofs.is_open()) {
    std::cerr << "There was a problem opening file\n";
    return false;
  }

  // Determine the number of channels and write the 'magic number'
  if (num_channels == 1) {
    ofs << "P5\n";
  } else {
    ofs << "P6\n";
  }

  // Write the width, height, and max value
  ofs << width << ' ' << height << "\n" << "255" << std::endl;

  // Write the pixels to the file
  int num_subpixels = width * height * num_channels;
  for (int i = 0; i < num_subpixels; i++) {
    ofs << data[i];
  }


  ofs.close();
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
