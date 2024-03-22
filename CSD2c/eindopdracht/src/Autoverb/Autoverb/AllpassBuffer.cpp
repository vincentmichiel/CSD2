//
//  AllpassBuffer.cpp
//  Autoverb
//
//  https://github.com/TimSchippers/CSD/blob/main/CSD2c/stereoEffect/circularBuffer.cpp
//

#include "AllpassBuffer.hpp"

AllpassBuffer::AllpassBuffer() : AllpassBuffer(256){};
AllpassBuffer::AllpassBuffer(int size)
    : indexWriteHead(0), indexReadHead(0), size(size) {
  setSize(size);
};

AllpassBuffer::~AllpassBuffer() { free(buffer); };

void AllpassBuffer::setDistanceReadHead(float samples) {
  // TODO check if distance is bigger than size to catch error
  distance = samples;
  indexReadHeadFloat = indexWriteHead - distance;
  indexReadHead = (int)indexReadHeadFloat;
  wrapHead(indexReadHead);
  wrapHeadFloat(indexReadHeadFloat);
};

void AllpassBuffer::setSize(int size) {
  // TODO check if size is smaller than num delaysamples to catch error
  free(buffer);
  this->size = size;
  buffer = (float *)malloc(size * sizeof(float));
  memset(buffer, 0, size * sizeof(float));
};
