#include "Track.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Track::Track(int number) : mNumber(number) {
  std::stringstream mapFileName;
  mapFileName << "Data/Track" << number << ".bmp";

  // Load bitmap using Allegro 5 function
  mBitmap = al_load_bitmap(mapFileName.str().c_str());

  if (!mBitmap) {
    std::cerr << "Failed to load bitmap: " << mapFileName.str() << std::endl;
  }
}

const TrackInfo Track::info() {
  TrackInfo info;

  stringstream infoFileName;
  infoFileName << "Data/Track" << mNumber << ".dat";

  ifstream ifs(infoFileName.str().c_str(), ios::binary);
  if (!ifs) {
    std::cerr << "Failed to open file: " << infoFileName.str() << std::endl;
    return info;
  }

  // Read binary data into info struct
  ifs.read((char *)&info, sizeof(info));

  if (ifs.fail()) {
    std::cerr << "Failed to read track info from file: " << infoFileName.str() << std::endl;
  }

  return info;
}
